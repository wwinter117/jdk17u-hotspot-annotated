/*
 * Copyright (c) 2019, Oracle and/or its affiliates. All rights reserved.
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

#ifndef SHARE_GC_Z_ZNMETHODTABLEITERATION_HPP
#define SHARE_GC_Z_ZNMETHODTABLEITERATION_HPP

#include "gc/z/zGlobals.hpp"

class NMethodClosure;

class ZNMethodTableEntry;

class ZNMethodTableIteration {
private:
    ZNMethodTableEntry *_table;
    size_t _size;
    ZCACHE_ALIGNED volatile size_t
    _claimed;

public:
    ZNMethodTableIteration();

    bool in_progress() const;

    void nmethods_do_begin(ZNMethodTableEntry *table, size_t size);

    void nmethods_do_end();

    void nmethods_do(NMethodClosure *cl);
};

#endif // SHARE_GC_Z_ZNMETHODTABLEITERATION_HPP
