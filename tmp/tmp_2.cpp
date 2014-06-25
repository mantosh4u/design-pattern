/***********************/
file "supported_format.h"
/***********************/

#include <gdkmm/pixbuf.h>
#include<vector>
#include<string>
#include<iostream>


class supported_format {
public:
		supported_format();
		void print_format_list();				
private:
	std::vector<std::string> namelist;	
};


supported_format::supported_format() {
	auto gdklist = Gdk::Pixbuf::get_formats();
	for(const auto& index: gdklist) {
		namelist.push_back(std::move(index.get_name()));
	}
}


void supported_format::print_format_list() {
	for(const auto& index: namelist) {
		std::cout<<index<<std::endl;
	}
	std::cout<<std::endl;
}



/**************************/
File  "myarea.h"
/***************************/
#include <gtkmm/drawingarea.h>
#include <gdkmm/pixbuf.h>
#include<string>

class MyArea : public Gtk::DrawingArea
{
public:
	MyArea(std::string fname);
	virtual ~MyArea();
protected:
	//Override default signal handler:
	virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
	Glib::RefPtr<Gdk::Pixbuf> m_image;
};






/*************************************/
File myarea.cpp
/*************************************/
#include"myarea.h"
#include<cairomm/context.h>
#include<gdkmm/general.h> // set_source_pixbuf()
#include<glibmm/fileutils.h>
#include<iostream>
#include<vector>

MyArea::MyArea(std::string fname) {
	try
	{
		// The fractal image has been created by the XaoS program.
		// http://xaos.sourceforge.net
		m_image = Gdk::Pixbuf::create_from_file(fname);
	}	
	catch(const Glib::FileError& ex)
	{
		std::cerr << "FileError: " << ex.what() << std::endl;
	}
	catch(const Gdk::PixbufError& ex)
	{
		std::cerr << "PixbufError: " << ex.what() << std::endl;
	}
	// Show at least a quarter of the image.
	if (m_image)
		set_size_request(m_image->get_width()/2, m_image->get_height()/2);
	}


MyArea::~MyArea() {
}


bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
	if (!m_image)
		return false;
		
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();
	// Draw the image in the middle of the drawing area, or (if the image is
	// larger than the drawing area) draw the middle part of the image.
	Gdk::Cairo::set_source_pixbuf(cr, m_image, (width - m_image->get_width())/2, (height - m_image->get_height())/2);
	cr->paint();
	return true;
}





/*************************/
File main.cpp
/*************************/
#include "myarea.h"
#include <gtkmm/main.h>
#include <gtkmm/window.h>
#include"supported_format.h"


int main(int argc, char** argv)
{
	Gtk::Main kit(argc, argv);
	
	supported_format formatlist;	
	formatlist.print_format_list();
	
	Gtk::Window win;
	win.set_title("ImageViewer");
	win.set_default_size(100, 100);

	std::string name{"test.JPG"};
	MyArea area(name);
	win.add(area);
	area.show();
	
	Gtk::Main::run(win);
	
	return 0;
}



















