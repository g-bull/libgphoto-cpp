#ifndef LIBGPHOTO_CPP_WIDGETS_WIDGET_H
#define LIBGPHOTO_CPP_WIDGETS_WIDGET_H
/*
 * libgphoto++ - modern c++ wrapper library for gphoto2
 * Copyright (C) 2016 Marco Gulino <marco AT gulinux.net>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "../fwd.h"
#include "../utils/dptr.h"
#include <list>
#include "../utils/logger.h"
namespace GPhotoCPP {

class Widget : public std::enable_shared_from_this<Widget>
{
public:
  Widget(CameraWidget *widget, const GPhotoCPP::GPhotoWrapperPtr &gphoto, const Logger::ptr &log);
  ~Widget();
  class StringValue;
  class RangeValue;
  class MenuValue;
  class ToggleValue;
  class DateValue;
  enum Type {String, Range, Toggle, Button, Date, Window, Section, Menu};
  Widgets children() const;
  Widgets all_children() const;
  
  WidgetPtr child_by_name(const std::string &name) const;
  WidgetPtr child_by_label(const std::string &label) const;
  
  std::string name() const;
  int id() const;
  std::string label() const;
  Type type() const;
  enum Access { ReadOnly, ReadWrite };
  Access access() const;
  
  bool operator==(const Widget &other) const;
  inline bool operator==(const WidgetPtr &other) const { return *other == *this; }
  bool operator!=(const Widget &other) const;
  inline bool operator!=(const WidgetPtr &other) const { return *other != *this; }
  
  WidgetPtr parent() const;
  
  std::string path() const;

  template<typename T> std::shared_ptr<T> get() { return std::shared_ptr<T>{new T(shared_from_this())}; }
  operator CameraWidget*() const; // TODO: remove
  
  template<typename V, typename C = V, typename Cs = C> class Value {
  public:
    typedef V Type;
    typedef std::shared_ptr<Value<V, C, Cs>> ptr;
    typedef std::function<Cs(V &)> V2C;
    typedef std::function<V(C c)> C2V;
    operator V() const { return value; }
    V get() const { return value; }
    Value &operator=(const V &value) { this->value = value; return *this; }
    void set(const V &value) { *this = value; }
    virtual ~Value() {
      if(original_value != value) {
	Cs c = v2c(value);
	widget->set_value(c);
      }
    }
    Value &refresh() {
      C c;
      widget->get_value(&c);
      value=c2v(c);
      original_value=c2v(c);
      return *this;
    }
  protected:
    Value(const WidgetPtr &widget, V2C v2c= [](V &v){ return v; }, C2V c2v = [](C c){ return V{c};}) : widget{widget}, v2c{v2c}, c2v{c2v} {
      refresh();
    }
    V value;
    V original_value;
    WidgetPtr widget;
    V2C v2c;
    C2V c2v;
  };
  
private:
  void get_value(void* value);
  void set_value(void* value);
  void set_value(const std::shared_ptr<void> &value);
  
    DPTR
};
}

std::ostream &operator<<(std::ostream& o, GPhotoCPP::Widget& w);
inline std::ostream &operator<<(std::ostream &o, const GPhotoCPP::WidgetPtr &w) { return o << *w; }
template<typename A, typename B, typename C> inline std::ostream &operator<<(std::ostream &o, const GPhotoCPP::Widget::Value<A, B, C> &v) { return o << v.get(); }
#endif // LIBGPHOTO_CPP_WIDGETS_WIDGET_H
