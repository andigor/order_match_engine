#include "order_book.h"

namespace ome {

std::pair<std::vector<buy_order>, bool> order_book::put_order(const sell_order& so)
{
  m_sell_orders.insert(so);
  return {};
}
std::pair<std::vector<sell_order>, bool> order_book::put_order(const buy_order& bo)
{
  m_buy_orders.insert(bo);
  return {};
}

void order_book::cancel_order(int id)
{

}

std::pair<std::vector<sell_order>, std::vector<buy_order>> order_book::get_orders_by_price() const
{
  return {};
}

std::set<uint32_t> order_book::get_buy_prices() const
{
  std::set<uint32_t> ret;
  for (const auto& val: m_buy_orders) {
    ret.insert(val.get_price());
  }
  return ret;
}

std::set<uint32_t> order_book::get_sell_prices() const
{
  std::set<uint32_t> ret;
  for (const auto& val: m_sell_orders) {
    ret.insert(val.get_price());
  }
  return ret;
}

}

