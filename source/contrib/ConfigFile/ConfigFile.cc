/* FILE_INFO_START
 * Copyright (C) 2016 
 * 
 * ***********************************************************************
 * This file is part of SpadSimulator
 * 
 * SpadSimulator is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * SpadSimulator is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SpadSimulator.  If not, see <http://www.gnu.org/licenses/>.
 * ***********************************************************************
 * 
 * File        : ConfigFile.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Apr 13 11:30:25 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


// ConfigFile.cpp

#include "ConfigFile.h"

using std::string;

ConfigFile::ConfigFile( string filename, string delimiter,
                        string comment, string sentry )
: myDelimiter(delimiter), myComment(comment), mySentry(sentry)
{
    // Construct a ConfigFile, getting keys and values from given file
  
    std::ifstream in( filename.c_str() );
  
    if( !in ) throw file_not_found( filename ); 
  
    in >> (*this);
}


ConfigFile::ConfigFile()
: myDelimiter( string(1,'=') ), myComment( string(1,'#') )
{
    // Construct a ConfigFile without a file; empty
}


void ConfigFile::remove( const string& key )
{
    // Remove key and its value
    myContents.erase( myContents.find( key ) );
    return;
}


bool ConfigFile::keyExists( const string& key ) const
{
    // Indicate whether key is found
    mapci p = myContents.find( key );
    return ( p != myContents.end() );
}


/* static */
void ConfigFile::trim( string& str )
{
    // Remove leading and trailing whitespace
    static const char whitespace[] = " \n\t\v\r\f";
    str.erase( 0, str.find_first_not_of(whitespace) );
    str.erase( str.find_last_not_of(whitespace) + 1U );
}


std::ostream& operator<<( std::ostream& os, const ConfigFile& cf )
{
    // Save a ConfigFile to os
    for( ConfigFile::mapci p = cf.myContents.begin(); p != cf.myContents.end(); ++p )
    {
        os << p->first << " " << cf.myDelimiter << " ";
        os << p->second << std::endl;
    }
    return os;
}


std::istream& operator>>( std::istream& is, ConfigFile& cf )
{
    // Load a ConfigFile from is
    // Read in keys and values, keeping internal whitespace
    typedef string::size_type pos;
    const string& delim  = cf.myDelimiter;  // separator
    const string& comm   = cf.myComment;    // comment
    const string& sentry = cf.mySentry;     // end of file sentry
    const pos skip = delim.length();        // length of separator
  
    string nextline = "";  // might need to read ahead to see where value ends
    
    while( is || nextline.length() > 0 )
    {
        // Read an entire line at a time
        string line;
        if( nextline.length() > 0 )
        {
            line = nextline;  // we read ahead; use it now
            nextline = "";
        }
        else
        {
            std::getline( is, line );
        }
    
        // Ignore comments
        line = line.substr( 0, line.find(comm) );
    
        // Check for end of file sentry
        if( sentry != "" && line.find(sentry) != string::npos ) return is;
    
        // Parse the line if it contains a delimiter
        pos delimPos = line.find( delim );
        if( delimPos < string::npos )
        {
            // Extract the key
            string key = line.substr( 0, delimPos );
            line.replace( 0, delimPos+skip, "" );
      
            // See if value continues on the next line
            // Stop at blank line, next line with a key, end of stream,
            // or end of file sentry
            bool terminate = false;
            while( !terminate && is )
            {
                std::getline( is, nextline );
                terminate = true;
                
                string nlcopy = nextline;
                ConfigFile::trim(nlcopy);
                if( nlcopy == "" ) continue;
                
                nextline = nextline.substr( 0, nextline.find(comm) );
                if( nextline.find(delim) != string::npos )
                continue;
                if( sentry != "" && nextline.find(sentry) != string::npos )
                continue;
                
                nlcopy = nextline;
                ConfigFile::trim(nlcopy);
                if( nlcopy != "" ) line += "\n";
                line += nextline;
                terminate = false;
            }
      
            // Store key and value
            ConfigFile::trim(key);
            ConfigFile::trim(line);
            cf.myContents[key] = line;  // overwrites if key is repeated
        }
    }
  
    return is;
}
