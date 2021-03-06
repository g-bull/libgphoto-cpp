#ifndef LIBGPHOTO_CPP_UTILS_DPTR_H
#define LIBGPHOTO_CPP_UTILS_DPTR_H
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

#include <memory>
#define DPTR class Private; friend class Private; const std::unique_ptr<Private> d;
#define dptr(...) d{new Private{__VA_ARGS__}}
#define DPTR_CLASS(name) class name::Private
#endif // LIBGPHOTO_CPP_UTILS_DPTR_H
