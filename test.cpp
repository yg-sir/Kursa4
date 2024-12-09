#include <UnitTest++/UnitTest++.h>
#include "DatabaseConnector.h"
#include "Calculate.h"
#include "Interface.h"
#include "Connection_of_client.h"
#include "Logger.h"
#include "Errors.h"

// Test for Calculator class
SUITE(CalculatorTests) {
    TEST(SumWithinLimits) {
        std::vector<uint16_t> data = {10, 20, 30};
        Calculator calc(data);
        CHECK_EQUAL(60, calc.send_res());
    }

    TEST(PositiveOverflow) {
        std::vector<uint16_t> data = {65535, 1};
        Calculator calc(data);
        CHECK_EQUAL(65535, calc.send_res());
    }
    TEST(AllZeros) {
        std::vector<uint16_t> data = {0, 0, 0};
        Calculator calc(data);
        CHECK_EQUAL(0, calc.send_res());
    }

    TEST(SingleElement) {
        std::vector<uint16_t> data = {123};
        Calculator calc(data);
        CHECK_EQUAL(123, calc.send_res());
    }
}
// Test for DatabaseConnector class
SUITE(DatabaseConnectorTests) {
    TEST(ValidDatabaseFile) {
        Connector_to_base connector;
        CHECK_EQUAL(0, connector.connect_to_base("file4test/base.txt"));
    }

    TEST(InvalidDatabaseFile) {
        Connector_to_base connector;
        CHECK_THROW(connector.connect_to_base("invalid.txt"), crit_err);
    }

    TEST(EmptyDatabaseFile) {
        Connector_to_base connector;
        CHECK_THROW(connector.connect_to_base("empty_base.txt"), crit_err);
    }
     TEST(DatabaseReconnection) {
        Connector_to_base connector;
        CHECK_EQUAL(0, connector.connect_to_base("file4test/base.txt"));
        CHECK_EQUAL(0, connector.connect_to_base("file4test/base.txt"));
    }
}

// Test for Logger class
SUITE(LoggerTests) {
    TEST(EmptyPath) {
        Logger logger;
        CHECK_THROW(logger.set_path(""), std::invalid_argument);
    }

    TEST(InvalidLogFilePath) {
        Logger logger;
        CHECK_THROW(logger.set_path("invalid_log"), std::invalid_argument);
    }

    TEST(LogWriting) {
        Logger logger("file4test/log.txt");
        CHECK_EQUAL(0, logger.writelog("Test log entry"));
    }
    
    TEST(newl_in_path_log) {
    	Logger logger;
    	CHECK_THROW(logger.set_path("file4test/base\n"), std::invalid_argument);
    	}
    TEST(MultipleLogEntries) {
        Logger logger("file4test/log.txt");
        CHECK_EQUAL(0, logger.writelog("First entry"));
        CHECK_EQUAL(0, logger.writelog("Second entry"));
    }
}

// Test for Client_Communicate class
SUITE(ClientCommunicateTests) {
    TEST(SHA224Hash) {
        std::string input = "test";
        std::string expected_hash = "730e109bd1659b36b90e4949471b3df9cf2d3847a20d2c86cd7c5a54"; 
        CHECK_EQUAL("90A3ED9E32B2AAF4C61C410EB925426119E1A9DC53D4286ADE99A809", Client_Communicate::sha224("test"));
        }
    TEST(InvalidHash) {
        std::string input = "different_input";
        std::string known_bad_hash = "00000000000000000000000000000000000000000000000000000000";
        CHECK(known_bad_hash != Client_Communicate::sha224(input));
    }
    TEST(EmptyStringHash) {
        std::string expected_empty_hash = "D14A028C2A3A2BC9476102BB288234C415A2B01F828EA62AC5B3E42F"; 
        CHECK_EQUAL(expected_empty_hash, Client_Communicate::sha224(""));
    }
    TEST(LongStringHash) {
        std::string long_input(1000, 'a');
        CHECK(Client_Communicate::sha224(long_input).length() > 0);
    }
}

int main(int argc, const char* argv[]) {
    return UnitTest::RunAllTests();
}
