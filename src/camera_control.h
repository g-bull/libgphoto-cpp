#ifndef LIBGPHOTO_CPP_CAMERA_CONTROL_H
#define LIBGPHOTO_CPP_CAMERA_CONTROL_H
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


#include "fwd.h"
#include "camera.h"
#include "utils/dptr.h"
namespace GPhotoCPP {

class GPhotoCPP::Camera::Control
{
public:
  ~Control();
  GPhotoCPP::Camera::ShotPtr shoot(const milliseconds &exposure, bool mirror_lock = false, seconds mirror_lock_duration = seconds{2});
private:
  friend class Camera;
  Control(const std::weak_ptr<GPhotoCPP::Camera>& camera, GPhotoCPP::Camera::Settings& settings, const GPhotoCPP::LoggerPtr& logger);
  DPTR
};
}

#endif // LIBGPHOTO_CPP_CAMERA_CONTROL_H