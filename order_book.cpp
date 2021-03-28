#include "order_book.h"

namespace ome {

std::pair<std::vector<buy_order>, bool> order_book::put_order(const sell_order& so)
{
  std::vector<buy_order> matched;
  auto cur_sell = so;
  for (;;) {
    if (m_buy_orders.is_empty()) {
      m_sell_orders.insert(cur_sell);
      return std::make_pair(matched, false);
    }

    auto& cur_buy = m_buy_orders.get_current();
    if (cur_sell.get_price() >= cur_buy.get_price()) {
      if (cur_sell.get_quantity() > cur_buy.get_quantity()) {
        matched.push_back(cur_buy);
        cur_sell.reduce_quantity(cur_buy.get_quantity());
        m_buy_orders.pop_order();
      }
      else if (cur_sell.get_quantity() < cur_buy.get_quantity()) {
        cur_buy.reduce_quantity(cur_sell.get_quantity());
        return std::make_pair(matched, true);
      }
      else {
        matched.push_back(cur_buy);
        m_buy_orders.pop_order();
        return std::make_pair(matched, true);
      }
    }
    else {
      m_sell_orders.insert(cur_sell);
      return std::make_pair(matched, false);
    }
  }
  assert(false);
  return {};
}
std::pair<std::vector<sell_order>, bool> order_book::put_order(const buy_order& bo)
{

  auto cur_buy = bo;

  std::vector<sell_order> matched;
  for (;;) {
    if (m_sell_orders.is_empty()) {
      m_buy_orders.insert(cur_buy);
      return std::make_pair(matched, false);
    }
    auto& cur_sell = m_sell_orders.get_current();
    if (cur_sell.get_price() >= cur_buy.get_price()) {
      // can trade
      if (cur_sell.get_quantity() > cur_buy.get_quantity()) {
        cur_sell.reduce_quantity(cur_buy.get_quantity());
        return std::make_pair(matched, true);
      }
      else if (cur_sell.get_quantity() < cur_buy.get_quantity()) {
        matched.push_back(cur_sell);
        cur_buy.reduce_quantity(cur_sell.get_quantity());
        m_sell_orders.pop_order();
      }
      else {
        matched.push_back(cur_sell);
        m_sell_orders.pop_order();
        return std::make_pair(matched, true); // exact match
      }
    }
    else {
      m_sell_orders.insert(cur_sell);
      return std::make_pair(matched, false);
    }
  }
  assert(false);
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
    ret.insert(val.second.get_price());
  }
  return ret;
}

std::set<uint32_t> order_book::get_sell_prices() const
{
  std::set<uint32_t> ret;
  for (const auto& val: m_sell_orders) {
    ret.insert(val.second.get_price());
  }
  return ret;
}

}

