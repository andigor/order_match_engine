

#include "order.h"
#include "order_book.h"

#include "acutest/include/acutest.h"

#include <iostream>
#include <chrono>

using namespace std::chrono;

void compare_sell_orders__compared_as_expected()
{
  {
    // equal orders are not less of each other
    ome::sell_order o1(1, 1, 1, system_clock::from_time_t(1));
    ome::sell_order o2(2, 1, 1, system_clock::from_time_t(1));
    TEST_CHECK(false == (o1 < o2));
    TEST_CHECK(false == (o2 < o1));
  }
  {
    // order of higher price is less which means goes first
    ome::sell_order o1(1, 1, 1, system_clock::from_time_t(1));
    ome::sell_order o2(2, 2, 1, system_clock::from_time_t(1));
    TEST_CHECK(true == (o1 < o2));
    TEST_CHECK(false == (o2 < o1));
  }
  {
    // order of lower time is less
    ome::sell_order o1(1, 1, 1, system_clock::from_time_t(1));
    ome::sell_order o2(2, 1, 1, system_clock::from_time_t(2));
    TEST_CHECK(true == (o1 < o2));
    TEST_CHECK(false == (o2 < o1));
  }
}


void compare_buy_orders__compared_as_expected()
{
  {
    // equal orders are not less of each other
    ome::buy_order o1(1, 1, 1, system_clock::from_time_t(1));
    ome::buy_order o2(2, 1, 1, system_clock::from_time_t(1));
    TEST_CHECK(false == (o1 < o2));
    TEST_CHECK(false == (o2 < o1));
  }
  {
    // order of higher price is less which means goes first
    ome::buy_order o1(1, 1, 1, system_clock::from_time_t(1));
    ome::buy_order o2(2, 2, 1, system_clock::from_time_t(1));
    TEST_CHECK(false == (o1 < o2));
    TEST_CHECK(true == (o2 < o1));
  }
  {
    // order of lower time is less
    ome::buy_order o1(1, 1, 1, system_clock::from_time_t(1));
    ome::buy_order o2(2, 1, 1, system_clock::from_time_t(2));
    TEST_CHECK(true == (o1 < o2));
    TEST_CHECK(false == (o2 < o1));
  }
}

TEST_LIST = {
     { "compare_sell_orders__compared_as_expected", compare_sell_orders__compared_as_expected}
   , { "compare_buy_orders__compared_as_expected", compare_buy_orders__compared_as_expected }
   , { NULL, NULL }
};
