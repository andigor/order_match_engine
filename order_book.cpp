#include "order_book.h"

namespace ome {

std::pair<std::vector<buy_order>, bool> order_book::put_order(const sell_order& so)
{
  return {};
}
std::pair<std::vector<sell_order>, bool> order_book::put_order(const buy_order& bo)
{
  return {};
}

void order_book::cancel_order(int id)
{

}

std::pair<std::vector<sell_order>, std::vector<buy_order>> order_book::orders_by_price() const
{
  return {};
}

std::set<uint32_t> order_book::buy_prices() const
{
  return std::set<uint32_t>();
}

std::set<uint32_t> order_book::sell_prices() const
{
  return std::set<uint32_t>();
}

}

