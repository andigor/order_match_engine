#pragma once

#include "order.h"

#include <map>
#include <vector>
#include <set>
#include <unordered_map>

namespace ome {


//template <class Cmp>
//class orders_map
//{
//public:
//  void insert_order(const order& o)
//  {
//    auto sorted_by_date = this->insert(o.get_price(), date_map());
//    // does not matter if it was inserted or not, ignoring res.second
//    sorted_by_date.first->emplace_pack(std::make_pair(o.get_time(), o));
//  }
//  void remove_order(const order& o)
//  {
//    auto sorted_by_date_iter = this->find(o.get_price());
//    assert(sorted_by_date_iter != this->end());
//    sorted_by_date_iter->erase(o.)
//  }
//private:
//  using date_map = std::multimap<order_time, order>;
//  using price_map = std::map<
// : public std::map<uint32_t, std::map<order_time, order>, Cmp>
//};

template<class Cmp>
class orders_queue
{
public:
  void insert(const order& o)
  {
    m_orders.insert(o);
  }
  void remove(const order& o)
  {

  }
private:
  std::multiset<order> m_orders;
};
class order_book
{
public:
  std::pair<std::vector<buy_order>, bool> put_order(const sell_order&);
  std::pair<std::vector<sell_order>, bool> put_order(const buy_order&);

  void cancel_order(int id);

  std::pair<std::vector<sell_order>, std::vector<buy_order>> orders_by_price() const;

  std::set<uint32_t> buy_prices() const;
  std::set<uint32_t> sell_prices() const;

private:
  std::set<buy_order> m_buy_orders;
  std::set<sell_order> m_sell_orders;

};

}

