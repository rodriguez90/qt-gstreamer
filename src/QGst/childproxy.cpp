/*
    Copyright (C) 2010  George Kiagiadakis <kiagiadakis.george@gmail.com>

    This library is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "childproxy.h"
#include <gst/gstobject.h>
#include <gst/gstchildproxy.h>

namespace QGst {

uint ChildProxy::childrenCount() const
{
    return gst_child_proxy_get_children_count(GST_CHILD_PROXY(object()));
}

ObjectPtr ChildProxy::childByName(const QGlib::String & name) const
{
    return ObjectPtr::wrap(gst_child_proxy_get_child_by_name(GST_CHILD_PROXY(object()), name), false);
}

ObjectPtr ChildProxy::childByIndex(uint index) const
{
    return ObjectPtr::wrap(gst_child_proxy_get_child_by_index(GST_CHILD_PROXY(object()), index), false);
}

bool ChildProxy::findChildProperty(const QGlib::String & name, ObjectPtr *obj, QGlib::ParamSpecPtr *paramSpec) const
{
    GstObject *op;
    GParamSpec *pp;
    bool result = gst_child_proxy_lookup(GST_OBJECT(object()), name, &op, &pp);
    if (result) {
        *obj = ObjectPtr::wrap(op, false);
        *paramSpec = QGlib::ParamSpecPtr::wrap(pp, false);
    }
    return result;
}

QGlib::Value ChildProxy::childProperty(const QGlib::String & name) const
{
    QGlib::ParamSpecPtr param;
    ObjectPtr object;
    if (findChildProperty(name, &object, &param)) {
        return object->property(param->name());
    } else {
        return QGlib::Value();
    }
}

}