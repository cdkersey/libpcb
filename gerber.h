#ifndef LIBPCB_GERBER_H
#define LIBPCB_GERBER_H

#include <iostream>
#include <map>
#include <string>

#include "point.h"

namespace libpcb {

// Available aperture shapes
enum aperture_t {
  AP_CIRCLE, AP_SQUARE
};

// The gerber file writer; the graphical output API.
class gerber {
public:
  gerber(std::ostream &out):
    out(out),
      mode_set(false), mode_clear(false), point_set(false), aperture_set(false),
      mode_region(false)
  { init(); }

  ~gerber() { out << "M02*" << std::endl; }

  // Set the drawing mode.
  void set_dark();
  void set_clear();

  // Create a region (filled area)
  void start_region();
  void end_region();
  
  // Set the current aperature (only circular supported)
  void set_aperture(double d, aperture_t shape = AP_CIRCLE);

  // Set current position.
  void move(point to);
  
  // Draw line segments in current aperture
  void draw(point to);
  void draw(point from, point to);

  // Draw "flash" in current aperture.
  void flash();
  void flash(point pt);
  
private:
  bool mode_set, mode_clear, point_set, aperture_set, mode_region;
  
  std::ostream &out;

  // Cache so we don't repeat ourselves
  std::map<std::pair<double, aperture_t>, std::string> apertures;
  point p; // Current point.
  double a; // Current aperture.
  aperture_t s; // Current aperture shape.

  void init();

  void coord(point pt); // Output coordinate in weird gerber format.
  void num(double d); // Output number in weird gerber format.
};
  
}

#endif
