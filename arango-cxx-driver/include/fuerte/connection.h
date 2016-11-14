#pragma once
#ifndef ARANGO_CXX_DRIVER_CONNECTION
#define ARANGO_CXX_DRIVER_CONNECTION

#include "common_types.h"
#include "connection_interface.h"

#include <memory>
#include <string>

namespace arangodb { namespace rest { inline namespace v2 {

class Database;

class Connection : public std::enable_shared_from_this<Connection> {
  friend class ConnectionBuilder;

    Connection(detail::ConnectionConfiguration conf);

  public:
    std::shared_ptr<Database> getDatabase(std::string name);
    std::shared_ptr<Database> createDatabase(std::string name);
    bool deleteDatabase(std::string name);

    Request sendRequest(Request&& r){
      return _realConnection->sendRequest(std::move(r));
    };
    void sendRequest(Request r, ErrorCallback e, RequestCallback c){
      return _realConnection->sendRequest(std::move(r), e, c);
    };

  private:
    std::shared_ptr<ConnectionImplInterface>  _realConnection;
    detail::ConnectionConfiguration _configuration;

};


/** The connection Builder is a class that allows the easy configuration of
 *  connections. We decided to use the builder pattern because the connections
 *  have too many options to put them all in a single constructor. When you have
 *  passed all your options call connect() in order to receive a shared_ptr to a
 *  connection. Remember to use the "->" operator to access the connections
 *  members.
 */
class ConnectionBuilder {
  public:
    ConnectionBuilder& host(std::string const&); // takes url in the form  (http|vst)[s]://(ip|hostname):port
                                                 // sets protocol host and port
    //ConnectionBuilder() = delete;
    //ConnectionBuilder(std::string const& s){
    //  host(s);
    //};

    std::shared_ptr<Connection> connect(){
      return std::shared_ptr<Connection>( new Connection(_conf)) ;
    }

    ConnectionBuilder& async(bool b){ _conf._async = b; return *this; }
    ConnectionBuilder& user(std::string const& u){ _conf._user = u; return *this; }
    ConnectionBuilder& password(std::string const& p){ _conf._password = p; return *this; }
    ConnectionBuilder& maxChunkSize(std::size_t c){ _conf._maxChunkSize = c; return *this; }

  private:
    detail::ConnectionConfiguration _conf;
};

}}}
#endif
