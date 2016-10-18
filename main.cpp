#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "avalanche.hh"
#include "avalanche_simulator.hh"
#include "build_config.hh"
#include "csv_event_importer.hh"
#include "excel_config_importer.hh"
#include "excel_lookup_table.hh"
#include "isensor_configuration.hh"
#include "isensor_matrix.hh"
#include "laser_event_importer.hh"
#include "log.hh"
#include "photon.hh"
#include "random.hh"
#include "root_event_importer.hh"
#include "root_simulation_exporter.hh"
#include "silicon_factory.hh"
#include "sipm_matrix_factory.hh"
#include "spad_configuration.hh"
#include "spad_matrix_factory.hh"
#include "string_cast.hh"

#include "ConfigFile.h"

const std::string AFTERPULSE_GENERATOR_KEY              = "afterpulse_generator";
const std::string AVALANCHE_FILTER_KEY                  = "avalanche_filter";
const std::string BATCH_SIZE_KEY                        = "batch_size";
const std::string BATCH_INDEX_KEY                       = "batch_index";
const std::string CROSSTALK_GENERATOR_KEY               = "crosstalk_generator";
const std::string DARK_COUNT_GENERATOR_KEY              = "dark_count_generator";
const std::string EVENT_IMPORTER_KEY                    = "event_importer";
const std::string EVENT_FILE_KEY                        = "event_file";
const std::string LASER_PHOTONS_PER_EVENT_KEY           = "laser_photons_per_event";
const std::string LASER_WAVELENGTH_KEY                  = "laser_wavelength";
const std::string MATRIX_FACTORY_KEY                    = "matrix_factory";
const std::string QUENCH_FACTORY_KEY                    = "quench_factory";
const std::string SEED_KEY                              = "random_seed";
const std::string SILICON_FACTORY_KEY                   = "silicon_factory";
const std::string SILICON_OPTICAL_PROPERTIES_FILE_KEY   = "silicon_optical_properties_file";
const std::string SIMULATOR_EXPORTER_KEY               = "simulation_exporter";
const std::string SIMULATOR_FILE_KEY                   = "simulation_file";
const std::string SIMULATOR_CONFIG_IMPORTER_KEY         = "simulator_config_importer";
const std::string SIMULATOR_CONFIG_FILE_KEY             = "simulator_config_file";
const std::string THERMAL_NOISE_DELAY_KEY               = "thermal_noise_delay";
const std::string VERBOSE_KEY                           = "verbose_level";

const std::string OVERBIAS_OVERWRITE_KEY                = "overbias_ow";
const std::string DARK_COUNT_RATE_OVERWRITE_KEY         = "dark_count_rate_ow";
const std::string AFTERPULSE_PROB_OVERWRITE_KEY         = "afterpulse_prob_ow";
const std::string SPAD_JITTER_OVERWRITE_KEY             = "spad_jitter_ow";

const std::string FILE_MANAGER_CSV                      = "CSV";
const std::string FILE_MANAGER_EXCEL                    = "Excel";
const std::string FILE_MANAGER_LASER                    = "Laser";
const std::string FILE_MANAGER_ROOT                     = "Root";

const std::string SENSOR_SPAD                           = "Spad";
const std::string SENSOR_SIPM                           = "Sipm";

const std::string DEFAULT_VALUE                         = "Default";

void printUsage()
{
    std::cout << "**************************************************************" << std::endl;
    std::cout << "*                      Timestamps Usage                      *" << std::endl;
    std::cout << "**************************************************************" << std::endl;
    std::cout << "                                                              " << std::endl;
    std::cout << "Timestamps configuration_file                                 " << std::endl;
    std::cout << "                                                              " << std::endl;
    std::cout << "  configuration_file                                          " << std::endl;
    std::cout << "    The path of configuration file for this run.              " << std::endl;
    std::cout << "                                                              " << std::endl;
}

void checkSensorConfigOverwrite(const ConfigFile& config, Map<std::string, std::string>& sensorConfig) 
{
    bool stop = true;
    double overbias;
    if (config.keyExists(OVERBIAS_OVERWRITE_KEY)) {
        stop = false;
        overbias = config.read<double>(OVERBIAS_OVERWRITE_KEY);
        std::string strOverbias;
        castFrom<double>(overbias, strOverbias);
        sensorConfig[SpadConfiguration::OVERBIAS] = strOverbias;
    }
    
    if (!stop && config.keyExists(AFTERPULSE_PROB_OVERWRITE_KEY)) {
        ExcelLookupTable lookupTable (config.read<std::string>(AFTERPULSE_PROB_OVERWRITE_KEY));
        double afterpulseProb = lookupTable.interpolateValue(overbias);
        std::string strAfterpulseProb;
        castFrom<double>(afterpulseProb, strAfterpulseProb);
        sensorConfig[SpadConfiguration::AFTERPULSING_PROB] = strAfterpulseProb;
    }
    
    if (!stop && config.keyExists(DARK_COUNT_RATE_OVERWRITE_KEY)) {
        ExcelLookupTable lookupTable (config.read<std::string>(DARK_COUNT_RATE_OVERWRITE_KEY));
        double dcr = lookupTable.interpolateValue(overbias);
        std::string strDcr;
        castFrom<double>(dcr, strDcr);
        sensorConfig[SpadConfiguration::DCR_RATE] = strDcr;
    }
    
    if (!stop && config.keyExists(SPAD_JITTER_OVERWRITE_KEY)) {
        ExcelLookupTable lookupTable (config.read<std::string>(SPAD_JITTER_OVERWRITE_KEY));
        double spadJitter = lookupTable.interpolateValue(overbias);
        std::string strSpadJitter;
        castFrom<double>(spadJitter, strSpadJitter);
        sensorConfig[SpadConfiguration::SPAD_JITTER] = strSpadJitter;
    }
}

ConfigImporter* getConfigImporterFromConfig(const ConfigFile& config)
{
    ConfigImporter* importer = 0;
    
    if (!config.keyExists(SIMULATOR_CONFIG_IMPORTER_KEY) || !config.keyExists(SIMULATOR_CONFIG_FILE_KEY)) {
        LOG_STREAM(1) << "Both \"" << SIMULATOR_CONFIG_IMPORTER_KEY << "\" and \"" << SIMULATOR_CONFIG_FILE_KEY << "\" must be in the config file.";
        throw std::invalid_argument("Missing config. See verbose 1.");
    }
    
    std::string type = config.read<std::string>(SIMULATOR_CONFIG_IMPORTER_KEY);
    std::string path = config.read<std::string>(SIMULATOR_CONFIG_FILE_KEY);
    std::string siliconFile = config.read<std::string>(SILICON_OPTICAL_PROPERTIES_FILE_KEY, "");
    
    if (type == FILE_MANAGER_EXCEL) {
        if (siliconFile == "") {
            importer = new ExcelConfigImporter(path);
        } else {
            importer = new ExcelConfigImporter(path, siliconFile);
        }
    } else {
        LOG_STREAM(1) << "The Simulator Config Importer type \"" << type << "\" is not implemented or not recognized.";
        throw std::invalid_argument("Unrecognized Simulator Config Importer type. See verbose 1.");
    }
    
    return importer;
}

ISimulator* getSimulatorFromConfig(const ConfigFile& config)
{
    AvalancheSimulator* simulator = new AvalancheSimulator();
    ConfigImporter* importer = getConfigImporterFromConfig(config);
    std::string type;
    
    if (config.keyExists(SILICON_FACTORY_KEY)) {
        type = config.read<std::string>(SILICON_FACTORY_KEY);
        Vector<double> wavelengths, coefficients;
        importer->getSiliconOpticalProperties(wavelengths, coefficients);
        if (type == DEFAULT_VALUE) {
            if (wavelengths.size() > 0) {
                simulator->setSiliconFactory(new SiliconFactory(wavelengths, coefficients));
            }
        } else {
            LOG_STREAM(1) << "The Silicon Factory type \"" << type << "\" is not implemented or not recognized.";
            throw std::invalid_argument("Unrecognized Silicon Factory type. See verbose 1.");
        }
    }
    
    if (config.keyExists(QUENCH_FACTORY_KEY)) {
        type = config.read<std::string>(QUENCH_FACTORY_KEY);
        if (type != DEFAULT_VALUE) {
            LOG_STREAM(1) << "The Quench Factory type \"" << type << "\" is not implemented or not recognized.";
            throw std::invalid_argument("Unrecognized Quench Factory type. See verbose 1.");
        }
    }
    
    if (config.keyExists(MATRIX_FACTORY_KEY)) {
        type = config.read<std::string>(MATRIX_FACTORY_KEY);
        if (type == SENSOR_SPAD) {
            SpadMatrixFactory* matrixFactory = new SpadMatrixFactory();
            simulator->setSensorMatrixFactory(matrixFactory);
        } else if (type == SENSOR_SIPM) {
            SipmMatrixFactory* matrixFactory = new SipmMatrixFactory();
            simulator->setSensorMatrixFactory(matrixFactory);
        } else if (type != DEFAULT_VALUE) {
            LOG_STREAM(1) << "The Sensor Matrix Factory type \"" << type << "\" is not implemented or not recognized.";
            throw std::invalid_argument("Unrecognized Sensor Matrix type. See verbose 1.");
        }
    }
    
    if (config.keyExists(AFTERPULSE_GENERATOR_KEY)) {
        type = config.read<std::string>(AFTERPULSE_GENERATOR_KEY);
        if (type != DEFAULT_VALUE) {
            LOG_STREAM(1) << "The Afterpulse Generator type \"" << type << "\" is not implemented or not recognized.";
            throw std::invalid_argument("Unrecognized Afterpulse Generator type. See verbose 1.");
        }
    }
    
    if (config.keyExists(CROSSTALK_GENERATOR_KEY)) {
        type = config.read<std::string>(CROSSTALK_GENERATOR_KEY);
        if (type != DEFAULT_VALUE) {
            LOG_STREAM(1) << "The Crosstalk Generator type \"" << type << "\" is not implemented or not recognized.";
            throw std::invalid_argument("Unrecognized Crosstalk Generator type. See verbose 1.");
        }
    }
    
    if (config.keyExists(DARK_COUNT_GENERATOR_KEY)) {
        type = config.read<std::string>(DARK_COUNT_GENERATOR_KEY);
        if (type != DEFAULT_VALUE) {
            LOG_STREAM(1) << "The DarkCount Generator type \"" << type << "\" is not implemented or not recognized.";
            throw std::invalid_argument("Unrecognized DarkCount Generator type. See verbose 1.");
        }
    }
    
    Map<std::string, std::string> sensorConfig = importer->getSensorConfig();
    checkSensorConfigOverwrite(config, sensorConfig);
    
    simulator->init(importer->getSiliconConfig(),
                    importer->getQuenchConfig(),
                    sensorConfig,
                    importer->getMatrixConfig());
    
    delete importer;
    
    return simulator;
}

EventImporter* getEventImporterFromConfig(const ConfigFile& config)
{
    EventImporter* importer = 0;
    
    if (!config.keyExists(EVENT_IMPORTER_KEY)) {
        LOG_STREAM(1) << "The parameter \"" << EVENT_IMPORTER_KEY << "\" must be in the config file.";
        throw std::invalid_argument("Missing config. See verbose 1.");
    }
    
    std::string type = config.read<std::string>(EVENT_IMPORTER_KEY);

    if (type == FILE_MANAGER_ROOT) {
        if (!config.keyExists(EVENT_FILE_KEY)) {
            LOG_STREAM(1) << "The parameter \"" << EVENT_FILE_KEY << "\" must be in the config file.";
            throw std::invalid_argument("Missing config. See verbose 1.");
        }
        std::string path = config.read<std::string>(EVENT_FILE_KEY);
        importer = new RootEventImporter(path);
    } else if (type == FILE_MANAGER_LASER) {
        if (!config.keyExists(LASER_PHOTONS_PER_EVENT_KEY) || !config.keyExists(LASER_WAVELENGTH_KEY)) {
            LOG_STREAM(1) << "Both parameters \"" << LASER_PHOTONS_PER_EVENT_KEY 
                << "\" and \"" << LASER_WAVELENGTH_KEY << "\" must be in the config file.";
            throw std::invalid_argument("Missing config. See verbose 1.");
        }
        int photonsPerEvent = config.read<int>(LASER_PHOTONS_PER_EVENT_KEY);
        double wavelength = config.read<double>(LASER_WAVELENGTH_KEY);
        importer = new LaserEventImporter(photonsPerEvent, wavelength);
    } else if (type == FILE_MANAGER_CSV) {
        if (!config.keyExists(EVENT_FILE_KEY)) {
            LOG_STREAM(1) << "The parameter \"" << EVENT_FILE_KEY << "\" must be in the config file.";
            throw std::invalid_argument("Missing config. See verbose 1.");
        }
        std::string path = config.read<std::string>(EVENT_FILE_KEY);
        importer = new CsvEventImporter(path);
    } else {
        LOG_STREAM(1) << "The Event Importer type \"" << type << "\" is not implemented or not recognized.";
        throw std::invalid_argument("Unrecognized Event Importer type. See verbose 1.");
    }
    
    return importer;
}

SimulationExporter* getSimulationExporterFromConfig(const ConfigFile& config)
{
    SimulationExporter* exporter = 0;
    
    if (!config.keyExists(SIMULATOR_EXPORTER_KEY) || !config.keyExists(SIMULATOR_FILE_KEY)) {
        LOG_STREAM(1) << "Both \"" << SIMULATOR_EXPORTER_KEY << "\" and \"" << SIMULATOR_FILE_KEY << "\" must be in the config file.";
        throw std::invalid_argument("Missing config. See verbose 1.");
    }
    
    std::string type = config.read<std::string>(SIMULATOR_EXPORTER_KEY);
    std::string path = config.read<std::string>(SIMULATOR_FILE_KEY);
    std::string filter = config.read<std::string>(AVALANCHE_FILTER_KEY, "");
    
    if (type == FILE_MANAGER_ROOT) {
        exporter = new RootSimulationExporter(path, filter);
    } else {
        LOG_STREAM(1) << "The Simulation Exporter type \"" << type << "\" is not implemented or not recognized.";
        throw std::invalid_argument("Unrecognized Simulation Exporter type. See verbose 1.");
    }
    
    return exporter;
}

void timestamp(ISimulator&         simulator, 
               EventImporter&      importer, 
               SimulationExporter& exporter,
               const double&       delay,
               const int&          batchSize,
               const int&          batchSkipped,
               const int&          randomSeed)
{
    Vector<Photon*> photons;
    Vector<Avalanche*> avalanches;
    int eventIndex;
    
#ifdef VERBOSE
    int progressionLog = 0;
    double progression;
    LOG_STREAM(1) << "batchSize: " << batchSize << " " << std::endl;
    LOG_STREAM(1) << "Set delay: " << delay << " ns" << std::endl;
#endif // VERBOSE
    for (int i = 0; i < batchSize; ++i) {
#ifdef VERBOSE
        progression = (double) i / (double) batchSize;
        if ((int) (progression * 100) != progressionLog) {
            progressionLog = (int) (progression * 100);
            LOG_STREAM(1) << "Progression: " << progressionLog << "%, Event : #" << i << std::endl;
        }
#endif //VERBOSE
        eventIndex = i + batchSkipped * batchSize;
        RandomGenerator::seed(eventIndex+randomSeed);
        importer.importSingleEvent(eventIndex, *simulator.getSensorMatrix(), delay, photons);
        simulator.simulateAll(photons, avalanches);
        exporter.exportSimulation(eventIndex, photons.size(), avalanches);
        photons.clearAndDelete();
        avalanches.clearAndDelete();
        simulator.resetMatrix();
    }
}

void timestamp(const ConfigFile& config)
{
    VERBOSE_MAX = config.read<int>(VERBOSE_KEY, 1);
    double delay = config.read<double>(THERMAL_NOISE_DELAY_KEY, 50.0);
    int batchSize = config.read<int>(BATCH_SIZE_KEY, 10);
    int batchIndex = config.read<int>(BATCH_INDEX_KEY, 0);
    int randomSeed = config.read<int>(SEED_KEY, 0);

    #ifdef VERBOSE
        LOG_STREAM(0) << "Verbose Level is : " << VERBOSE_MAX << " " << std::endl;
        LOG_STREAM(1) << "Starting simulation with the following configuration" << std::endl;
        string importer_type = config.read<std::string>(EVENT_IMPORTER_KEY);
        LOG_STREAM(1) << "Importer Type: " <<  importer_type << std::endl;
        if (importer_type==FILE_MANAGER_LASER) {
            LOG_STREAM(1) << "Number of laser photons: " << config.read<std::string>(LASER_PHOTONS_PER_EVENT_KEY)  << std::endl;
            LOG_STREAM(1) << "Wavelength of laser photons: " << config.read<std::string>(LASER_WAVELENGTH_KEY )  << std::endl;
        } else {
            LOG_STREAM(1) << "Imported file path: " << config.read<std::string>(EVENT_FILE_KEY)  << std::endl;
        }

        LOG_STREAM(1) << "Configuration file type: " << config.read<std::string>(SIMULATOR_CONFIG_IMPORTER_KEY)  << std::endl;
        LOG_STREAM(1) << "Configuration file path: " << config.read<std::string>(SIMULATOR_CONFIG_FILE_KEY)  << std::endl;
        LOG_STREAM(1) << "Exported file type: " << config.read<std::string>(SIMULATOR_EXPORTER_KEY)  << std::endl;
        LOG_STREAM(1) << "Exported file path: " << config.read<std::string>(SIMULATOR_FILE_KEY)  << std::endl;
        LOG_STREAM(1) << "Seed for random generator: " << randomSeed  << std::endl;
    #endif // VERBOSE


    
    ISimulator* simulator = getSimulatorFromConfig(config);
    EventImporter* importer = getEventImporterFromConfig(config);
    SimulationExporter * exporter = getSimulationExporterFromConfig(config);
    
    timestamp(*simulator, *importer, *exporter, delay, batchSize, batchIndex, randomSeed);
    
    delete simulator;
    delete importer;
    delete exporter;
}

int main(int argc, char* argv[]) 
{
    if (argc < 2) {
        printUsage();
        exit(1);
    }

    clock_t tStart = clock();

    ConfigFile config(argv[1]);
    timestamp(config);
    
    printf("Time taken: %.2fs\n", double(clock() - tStart)/ CLOCKS_PER_SEC);
}
