/*
 * Copyright (c) 2016, 2020, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 */

#ifndef OS_LINUX_GC_Z_ZMOUNTPOINT_LINUX_HPP
#define OS_LINUX_GC_Z_ZMOUNTPOINT_LINUX_HPP

#include "gc/z/zArray.hpp"
#include "memory/allocation.hpp"

class ZMountPoint : public StackObj {
private:
    char *_path;

    char *get_mountpoint(const char *line,
                         const char *filesystem) const;

    void get_mountpoints(const char *filesystem,
                         ZArray<char *> *mountpoints) const;

    void free_mountpoints(ZArray<char *> *mountpoints) const;

    char *find_preferred_mountpoint(const char *filesystem,
                                    ZArray<char *> *mountpoints,
                                    const char **preferred_mountpoints) const;

    char *find_mountpoint(const char *filesystem,
                          const char **preferred_mountpoints) const;

public:
    ZMountPoint(const char *filesystem, const char **preferred_mountpoints);

    ~ZMountPoint();

    const char *get() const;
};

#endif // OS_LINUX_GC_Z_ZMOUNTPOINT_LINUX_HPP
