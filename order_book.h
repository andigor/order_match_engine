#pragma once

#include "order.h"

#include <map>
#include <vector>
#include <set>
#include <unordered_map>

namespace ome {

template <class Order>
class orders_queue
{
public:
  void insert(const Order& o)
  {
    m_orders.insert(o);
  }
  void pop_order()
  {
    assert(!m_orders.empty());
    auto iter = begin();
    m_orders.erase(iter);
  }
  Order get_current() const
  {
    assert(!m_orders.empty());

    auto iter = begin();
    return *iter;
  }


  //void remove(const order& o)
  //{

  //}
  auto begin() const
  {
    return m_orders.begin();
  }
  auto end() const
  {
    return m_orders.begin();
  }
  size_t get_size() const
  {
    return m_orders.size();
  }
private:
  std::multiset<Order> m_orders;
};
class order_book
{
public:
  std::pair<std::vector<buy_order>, bool> put_order(const sell_order&);
  std::pair<std::vector<sell_order>, bool> put_order(const buy_order&);

  void cancel_order(int id);

  std::pair<std::vector<sell_order>, std::vector<buy_order>> get_orders_by_price() const;

  std::set<uint32_t> get_buy_prices() const;
  std::set<uint32_t> get_sell_prices() const;

private:
  std::set<buy_order> m_buy_orders;
  std::set<sell_order> m_sell_orders;

};

}

