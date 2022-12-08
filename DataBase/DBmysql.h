//
// Created by Chuanchao Lyu on 2022/11/27.
//

#ifndef CPP17_DBMYSQL_H
#define CPP17_DBMYSQL_H

#include "LogWrapper.h"
#include <mysql++/mysql++.h>
#include <unordered_map>
#include <mutex>
#include "MysqlUtility.h"

namespace HFTrading{
    struct StockScore{
        std::string code;
        std::string tradedate;
        double score;
        std::string toString() const{return tradedate + "==" + code + "==" + std::to_string(score);}
        template<typename OStream>
        friend OStream& operator<<(OStream& io,const StockScore& ss){
            io << ss.tradedate << "==" << ss.code << "==" << ss.score << std::endl;
            return io;
        }
    };



    struct mysqlinfo{
       std::string ip;
       unsigned int port;
       std::string name;
       std::string user;
       std::string password;
    };

    class DBmysql:private MysqlUtility{
    public:
        static std::unique_ptr<DBmysql> CreateDBmysql();
        DBmysql()=default;
        ~DBmysql()=default;
        void init(const std::string& config="../../config/DBconfig", const std::string& logger="cpp17");
        bool QueryShortScore(const std::string&db, const std::string& date,std::vector<StockScore>& ss);
    private:
        void ParseShortScore(const mysqlpp::StoreQueryResult&,std::vector<StockScore>&);
    private:
        struct safeconn{
        mysqlpp::Connection conn{false};
        std::mutex mtx;
        };
        std::shared_ptr<spdlog::logger> m_logger;
        std::unordered_map<std::string, safeconn> m_dbs;
    };


}
#endif //CPP17_DBMYSQL_H
