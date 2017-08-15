//inheritance (derived class with a base class in namspeace NS)
// https://stackoverflow.com/questions/4326176/inheritance-and-namespaces

#include <dlib/gui_widgets.h>
#include <iostream>
#include <string>

namespace dlib{

class color_box : public draggable{
private:
  unsigned char red, green, blue;
public: 
  color_box(
    drawable_window &w,
    rectangle &area,
    unsigned char r,
    unsigned char g,
    unsigned char b)
  : draggable(w),
    red(r),
    green(g),
    blue(b) {
      rect = area;
      set_draggable_area(rectangle(10,10,400,400));
      enable_events();
    }

    ~color_box(){
      disable_events();
      parent.invalidate_rectangle(rect);
    }

private:
  void draw(const canvas &c) const{
    rectangle area = c.intersect(rect);
    if (area.is_empty()){ return; }

    fill_rect(c, rect, rgb_pixel(red, green, blue));
  }

};

class win: public drawable_window{
private:
  unsigned long counter;
  label c;
  button b;
  color_box cb;
  menu_bar mbar;

  void on_button_clicked(){
    ++counter;
    std::ostringstream sout;
    sout << "counter: " << counter;
    c.set_text(sout.str());
  }
public:
  win() : counter(0),
          c(*this),
          b(*this),
          cb(*this, rectangle(100,100,200,200), 0, 0, 255),
          mbar(*this)
  {
    b.set_pos(10,60);
    b.set_name("buttom");

    c.set_pos(b.left(), b.bottom()+5);
    b.set_click_handler(*this, &win::on_button_clicked);

    mbar.set_number_of_menus(1);
    mbar.set_menu_name(0, "Menu", 'M');

    mbar.menu(0).add_menu_item(menu_item_text("Click Button!", *this, &win::on_button_clicked, 'C'));

    set_size(430, 380);
    set_title("dlib gui example");
    show();
  }

  ~win(){
    close_window();
  }
};

} //end namespace dlib


int main(){
  dlib::win mWindow;

  mWindow.wait_until_closed();
  return 0;
}

