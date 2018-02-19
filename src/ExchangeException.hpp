#pragma once
#include <stdexcept>
#include <string>


namespace exchange { 

class ExchangeException : public std::runtime_error {
 public :
  ExchangeException ( const std::string& aMessage ) 
      : std::runtime_error ( aMessage ) { }  
};



class ExchangeDBException  : public ExchangeException  { 
 public : 
  ExchangeDBException ( const std::string& aMessage ) 
      : ExchangeException ( aMessage ) {
  } 

}; 

} 



