#pragma once

#include <stddef.h>

#include <chrono>
#include <cassert>


namespace ome {
  using order_time = const std::chrono::time_point<std::chrono::system_clock>;

  class order
  {
  public:
    order(size_t id, uint32_t price, size_t quantity, const order_time& tm)
      : m_id(id)
      , m_price(price)
      , m_quantity(quantity)
      , m_time(tm)
    {

    }

    size_t get_id() const { return m_id; }
    uint32_t get_price() const { return m_price; }
    size_t get_quantity() const { return m_quantity; }
    order_time get_time() const { return m_time; }

  private:
    size_t m_id;
    uint32_t m_price;
    size_t m_quantity;
    order_time m_time;
  };

  class sell_order : public order
  {
  public:
    template <class ... Args>
    sell_order(Args&&... args) : order(std::forward<Args>(args)...)
    {

    }
    bool operator<(const order& other) const
    {
      if (get_price() > other.get_price()) {
        return true;
      }
      else if (get_price() < other.get_price()) {
        return false;
      }
      else {
        // if prices are the same then compare dates
        if (get_time() > other.get_time()) {
          return true;
        }
        else {
          return false;
        }
      }
    }
  };

  class buy_order : public order
  {
    template <class ... Args>
    buy_order(Args&&... args) : order(std::forward<Args>(args)...)
    {

    }
    bool operator<(const order& other) const
    {
      if (get_price() < other.get_price()) {
        return true;
      }
      else if (get_price() > other.get_price()) {
        return false;
      }
      else {
        // if prices are the same then compare dates
        if (get_time() > other.get_time()) {
          return true;
        }
        else {
          return false;
        }
      }
    }
  };

}
