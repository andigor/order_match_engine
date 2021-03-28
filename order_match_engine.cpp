

#include "order.h"
#include "order_book.h"

#include <iostream>
#include <chrono>

int main()
{
  ome::order_book book;
  ome::sell_order o1(1, 1, 1, std::chrono::system_clock::from_time_t(1));
  book.put_order(o1);
}

