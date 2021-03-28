

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

void put_same_buy_orders_to_queue__sorted_as_expected()
{
  ome::orders_queue<ome::buy_order> buy_queue;
  {
    // same orders
    ome::buy_order o1(1, 1, 1, system_clock::from_time_t(1));
    ome::buy_order o2(2, 1, 1, system_clock::from_time_t(1));
    ome::buy_order o3(3, 1, 1, system_clock::from_time_t(1));

    buy_queue.insert(o1);
    buy_queue.insert(o2);
    buy_queue.insert(o3);
  }

  {
    TEST_ASSERT(3 == buy_queue.get_size());
    auto o = buy_queue.get_current();
    TEST_CHECK(1 == o.get_price());
    TEST_CHECK(system_clock::from_time_t(1) == o.get_time());
    buy_queue.pop_order();
  }

  {
    TEST_ASSERT(2 == buy_queue.get_size());
    auto o = buy_queue.get_current();
    TEST_CHECK(1 == o.get_price());
    TEST_CHECK(system_clock::from_time_t(1) == o.get_time());
    buy_queue.pop_order();
  }

  {
    TEST_ASSERT(1 == buy_queue.get_size());
    auto o = buy_queue.get_current();
    TEST_CHECK(1 == o.get_price());
    TEST_CHECK(system_clock::from_time_t(1) == o.get_time());
    buy_queue.pop_order();
  }
  TEST_CHECK(0 == buy_queue.get_size());
}

void put_different_time_buy_orders_to_queue__sorted_as_expected()
{
  ome::orders_queue<ome::buy_order> buy_queue;
  {
    ome::buy_order o1(1, 1, 1, system_clock::from_time_t(3));
    ome::buy_order o2(2, 1, 1, system_clock::from_time_t(1));
    ome::buy_order o3(3, 1, 1, system_clock::from_time_t(2));

    buy_queue.insert(o1);
    buy_queue.insert(o2);
    buy_queue.insert(o3);
  }
  {
    TEST_ASSERT(3 == buy_queue.get_size());
    auto o = buy_queue.get_current();
    TEST_CHECK(2 == o.get_id());
    TEST_CHECK(system_clock::from_time_t(1) == o.get_time());
    buy_queue.pop_order();
  }
  {
    TEST_ASSERT(2 == buy_queue.get_size());
    auto o = buy_queue.get_current();
    TEST_CHECK(3 == o.get_id());
    TEST_CHECK(system_clock::from_time_t(2) == o.get_time());
    buy_queue.pop_order();
  }
  {
    TEST_ASSERT(1 == buy_queue.get_size());
    auto o = buy_queue.get_current();
    TEST_CHECK(1 == o.get_id());
    TEST_CHECK(system_clock::from_time_t(3) == o.get_time());
    buy_queue.pop_order();
  }
  TEST_CHECK(0 == buy_queue.get_size());
}

void put_different_price_buy_orders_to_queue__sorted_as_expected()
{
  ome::orders_queue<ome::buy_order> buy_queue;
  {
    ome::buy_order o1(1, 3, 1, system_clock::from_time_t(1));
    ome::buy_order o2(2, 2, 1, system_clock::from_time_t(1));
    ome::buy_order o3(3, 1, 1, system_clock::from_time_t(1));

    buy_queue.insert(o1);
    buy_queue.insert(o2);
    buy_queue.insert(o3);
  }
  {
    TEST_ASSERT(3 == buy_queue.get_size());
    auto o = buy_queue.get_current();
    TEST_CHECK(1 == o.get_id());
    TEST_CHECK(3 == o.get_price());
    buy_queue.pop_order();
  }
  {
    TEST_ASSERT(2 == buy_queue.get_size());
    auto o = buy_queue.get_current();
    TEST_CHECK(2 == o.get_id());
    TEST_CHECK(2 == o.get_price());
    buy_queue.pop_order();
  }
  {
    TEST_ASSERT(1 == buy_queue.get_size());
    auto o = buy_queue.get_current();
    TEST_CHECK(3 == o.get_id());
    TEST_CHECK(1 == o.get_price());
    buy_queue.pop_order();
  }
  TEST_CHECK(0 == buy_queue.get_size());
}

void put_same_sell_orders_to_queue__sorted_as_expected()
{
  ome::orders_queue<ome::sell_order> sell_queue;
  {
    // same orders
    ome::sell_order o1(1, 1, 1, system_clock::from_time_t(1));
    ome::sell_order o2(2, 1, 1, system_clock::from_time_t(1));
    ome::sell_order o3(3, 1, 1, system_clock::from_time_t(1));

    sell_queue.insert(o1);
    sell_queue.insert(o2);
    sell_queue.insert(o3);
  }

  {
    TEST_ASSERT(3 == sell_queue.get_size());
    auto o = sell_queue.get_current();
    TEST_CHECK(1 == o.get_price());
    TEST_CHECK(system_clock::from_time_t(1) == o.get_time());
    sell_queue.pop_order();
  }

  {
    TEST_ASSERT(2 == sell_queue.get_size());
    auto o = sell_queue.get_current();
    TEST_CHECK(1 == o.get_price());
    TEST_CHECK(system_clock::from_time_t(1) == o.get_time());
    sell_queue.pop_order();
  }

  {
    TEST_ASSERT(1 == sell_queue.get_size());
    auto o = sell_queue.get_current();
    TEST_CHECK(1 == o.get_price());
    TEST_CHECK(system_clock::from_time_t(1) == o.get_time());
    sell_queue.pop_order();
  }
  TEST_CHECK(0 == sell_queue.get_size());
}

void put_different_time_sell_orders_to_queue__sorted_as_expected()
{
  ome::orders_queue<ome::sell_order> sell_queue;
  {
    ome::sell_order o1(1, 1, 1, system_clock::from_time_t(3));
    ome::sell_order o2(2, 1, 1, system_clock::from_time_t(1));
    ome::sell_order o3(3, 1, 1, system_clock::from_time_t(2));

    sell_queue.insert(o1);
    sell_queue.insert(o2);
    sell_queue.insert(o3);
  }
  {
    TEST_ASSERT(3 == sell_queue.get_size());
    auto o = sell_queue.get_current();
    TEST_CHECK(2 == o.get_id());
    TEST_CHECK(system_clock::from_time_t(1) == o.get_time());
    sell_queue.pop_order();
  }
  {
    TEST_ASSERT(2 == sell_queue.get_size());
    auto o = sell_queue.get_current();
    TEST_CHECK(3 == o.get_id());
    TEST_CHECK(system_clock::from_time_t(2) == o.get_time());
    sell_queue.pop_order();
  }
  {
    TEST_ASSERT(1 == sell_queue.get_size());
    auto o = sell_queue.get_current();
    TEST_CHECK(1 == o.get_id());
    TEST_CHECK(system_clock::from_time_t(3) == o.get_time());
    sell_queue.pop_order();
  }
  TEST_CHECK(0 == sell_queue.get_size());
}

void put_different_price_sell_orders_to_queue__sorted_as_expected()
{
  ome::orders_queue<ome::sell_order> sell_queue;
  {
    ome::sell_order o1(1, 3, 1, system_clock::from_time_t(1));
    ome::sell_order o2(2, 2, 1, system_clock::from_time_t(1));
    ome::sell_order o3(3, 1, 1, system_clock::from_time_t(1));

    sell_queue.insert(o1);
    sell_queue.insert(o2);
    sell_queue.insert(o3);
  }
  {
    TEST_ASSERT(3 == sell_queue.get_size());
    auto o = sell_queue.get_current();
    TEST_CHECK(3 == o.get_id());
    TEST_CHECK(1 == o.get_price());
    sell_queue.pop_order();
  }
  {
    TEST_ASSERT(2 == sell_queue.get_size());
    auto o = sell_queue.get_current();
    TEST_CHECK(2 == o.get_id());
    TEST_CHECK(2 == o.get_price());
    sell_queue.pop_order();
  }
  {
    TEST_ASSERT(1 == sell_queue.get_size());
    auto o = sell_queue.get_current();
    TEST_CHECK(1 == o.get_id());
    TEST_CHECK(3 == o.get_price());
    sell_queue.pop_order();
  }
  TEST_CHECK(0 == sell_queue.get_size());
}

void put_one_order__no_trade()
{
  {
    ome::order_book book;
    auto traded = book.put_order(ome::buy_order(1, 1, 1, system_clock::from_time_t(1)));
    TEST_CHECK(0 == traded.first.size());
    TEST_CHECK(false == traded.second);
  }
  {
    ome::order_book book;
    auto traded = book.put_order(ome::sell_order(1, 1, 1, system_clock::from_time_t(1)));
    TEST_CHECK(0 == traded.first.size());
    TEST_CHECK(false == traded.second);
  }
}

void put_few_buy_orders__no_trade_expected_prices_returned()
{
  ome::order_book book;

  book.put_order(ome::buy_order(1, 1, 1, system_clock::from_time_t(1)));
  book.put_order(ome::buy_order(2, 1, 1, system_clock::from_time_t(1)));

  book.put_order(ome::buy_order(3, 2, 1, system_clock::from_time_t(1)));
  book.put_order(ome::buy_order(4, 2, 1, system_clock::from_time_t(2)));

  book.put_order(ome::buy_order(5, 3, 1, system_clock::from_time_t(1)));
  book.put_order(ome::buy_order(6, 4, 1, system_clock::from_time_t(2)));

  auto bp = book.get_buy_prices();
  TEST_ASSERT(4 == bp.size());
  TEST_CHECK(1 == bp.count(1));
  TEST_CHECK(1 == bp.count(2));
  TEST_CHECK(1 == bp.count(3));
  TEST_CHECK(1 == bp.count(4));

  auto sp = book.get_sell_prices();
  TEST_ASSERT(0 == sp.size());
}

void put_few_sell_orders__no_trade_expected_prices_returned()
{
  ome::order_book book;

  book.put_order(ome::sell_order(1, 1, 1, system_clock::from_time_t(1)));
  book.put_order(ome::sell_order(2, 1, 1, system_clock::from_time_t(1)));

  book.put_order(ome::sell_order(3, 2, 1, system_clock::from_time_t(1)));
  book.put_order(ome::sell_order(4, 2, 1, system_clock::from_time_t(2)));

  book.put_order(ome::sell_order(5, 3, 1, system_clock::from_time_t(1)));
  book.put_order(ome::sell_order(6, 4, 1, system_clock::from_time_t(2)));

  auto sp = book.get_sell_prices();
  TEST_ASSERT(4 == sp.size());
  TEST_CHECK(1 == sp.count(1));
  TEST_CHECK(1 == sp.count(2));
  TEST_CHECK(1 == sp.count(3));
  TEST_CHECK(1 == sp.count(4));

  auto bp = book.get_buy_prices();
  TEST_ASSERT(0 == bp.size());
}

void put_two_complete_match_orders_start_from_buy__trade_executed()
{
  ome::order_book book;
  {
    auto result = book.put_order(ome::buy_order(1, 10, 1, system_clock::from_time_t(1)));
    TEST_CHECK(true == result.first.empty());
    TEST_CHECK(false == result.second);
  }
  {
    auto result = book.put_order(ome::sell_order(2, 10, 1, system_clock::from_time_t(2)));
    TEST_ASSERT(1 == result.first.size());
    TEST_CHECK(1 == result.first[0].get_id());
    TEST_CHECK(true == result.second);
    TEST_CHECK(0 == book.get_buy_size());
    TEST_CHECK(0 == book.get_sell_size());
  }
}

void put_two_complete_match_orders_start_from_sell__trade_executed()
{
  ome::order_book book;
  {
    auto result = book.put_order(ome::sell_order(1, 10, 1, system_clock::from_time_t(1)));
    TEST_CHECK(true == result.first.empty());
    TEST_CHECK(false == result.second);
  }
  {
    auto result = book.put_order(ome::buy_order(2, 10, 1, system_clock::from_time_t(2)));
    TEST_ASSERT(1 == result.first.size());
    TEST_CHECK(1 == result.first[0].get_id());
    TEST_CHECK(true == result.second);
    TEST_CHECK(0 == book.get_buy_size());
    TEST_CHECK(0 == book.get_sell_size());
  }
}


TEST_LIST = {
     { "compare_sell_orders__compared_as_expected", compare_sell_orders__compared_as_expected}
   , { "compare_buy_orders__compared_as_expected", compare_buy_orders__compared_as_expected }

   , { "put_same_buy_orders_to_queue__sorted_as_expected", put_same_buy_orders_to_queue__sorted_as_expected}
   , { "put_different_time_buy_orders_to_queue__sorted_as_expected", put_different_time_buy_orders_to_queue__sorted_as_expected}
   , { "put_different_price_buy_orders_to_queue__sorted_as_expected", put_different_price_buy_orders_to_queue__sorted_as_expected}

   , { "put_same_sell_orders_to_queue__sorted_as_expected", put_same_sell_orders_to_queue__sorted_as_expected}
   , { "put_different_time_sell_orders_to_queue__sorted_as_expected", put_different_time_sell_orders_to_queue__sorted_as_expected}
   , { "put_different_price_sell_orders_to_queue__sorted_as_expected", put_different_price_sell_orders_to_queue__sorted_as_expected}

  ,  {"put_one_order__no_trade", put_one_order__no_trade}
  ,  {"put_few_sell_orders__no_trade_expected_prices_returned", put_few_sell_orders__no_trade_expected_prices_returned}
  ,  {"put_few_sell_orders__no_trade_expected_prices_returned", put_few_buy_orders__no_trade_expected_prices_returned}

  ,  {"put_two_complete_match_orders_start_from_sell__trade_executed", put_two_complete_match_orders_start_from_sell__trade_executed}
  ,  {"put_two_complete_match_orders_start_from_buy__trade_executed", put_two_complete_match_orders_start_from_buy__trade_executed}

   , { NULL, NULL }
};
