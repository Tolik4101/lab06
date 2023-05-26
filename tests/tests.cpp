#include <gtest/gtest.h>

#include "Transaction.h"
#include "Account.h"

TEST(Transaction, gee_test) {
    Account SBD();
    Account John(228, 101);
    Account James(1337, 0);
    Transaction transaction;
    EXPECT_TRUE(transaction.Make(John, James, 100));
}


TEST(Transaction, fee_check) {
    Account John(11, 100);
    Account Peter(12, 0);
    Transaction transaction;
    EXPECT_FALSE(transaction.Make(John, Peter, 100));
}

TEST(Transaction, id_check) {
    Account John(11, 100);
    Account Peter(11, 100);
    Transaction transaction;

    try {
        transaction.Make(John, Peter, 100);
        FAIL() << "expected error" << std::endl;
    } catch(std::logic_error& err) {
        EXPECT_EQ(err.what(), std::string("invalid action"));
    } catch(...) {
        FAIL() << "expected logic error" << std::endl;
    }
}

TEST(Transaction, sum_check) {
    Account John(1, 1000);
    Account Peter(12, 100);
    Transaction transaction;

    try {
        transaction.Make(John, Peter, -100);
        FAIL() << "expected error" << std::endl;
    } catch(std::invalid_argument& arg) {

        EXPECT_EQ(arg.what(), std::string("sum can't be negative"));
    } catch(...) {
        FAIL() << "expected argument error" << std::endl;
    }
}



TEST(Transaction, change_balance) {
    Account John(173, 1000);
    Account Peter(12, 100);
    try {
        John.ChangeBalance(30);
        FAIL() << "expected error" << std::endl;
    } catch(std::runtime_error& time) {
        EXPECT_EQ(time.what(), std::string("at first lock the account"));
    } catch(...) {
        FAIL() << "expected time error" << std::endl;
    }
}