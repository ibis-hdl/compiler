#pragma once

#include <ibis/util/cxx_bug_fatal.hpp>

namespace ibis::support::rapidjson {

///
/// See:
/// - [How to merge two json file using rapidjson](
///   https://stackoverflow.com/questions/40013355/how-to-merge-two-json-file-using-rapidjson)
///
inline void merge_object(::rapidjson::Value& dest, ::rapidjson::Value& src,
                         ::rapidjson::Document::AllocatorType& allocator)
{
    for (auto src_iter = src.MemberBegin(); src_iter != src.MemberEnd(); ++src_iter) {
        auto dest_iter = dest.FindMember(src_iter->name);

        if (dest_iter != dest.MemberEnd()) {
            cxx_assert(src_iter->value.GetType() == dest_iter->value.GetType(),
                       "JSON type mismatch");

            if (src_iter->value.IsArray()) {
                for (auto arrayIt = src_iter->value.Begin(); arrayIt != src_iter->value.End();
                     ++arrayIt) {
                    dest_iter->value.PushBack(*arrayIt, allocator);
                }
            }
            else if (src_iter->value.IsObject()) {
                merge_object(dest_iter->value, src_iter->value, allocator);
            }
            else {
                dest_iter->value = src_iter->value;
            }
        }
        else {
            dest.AddMember(src_iter->name, src_iter->value, allocator);
        }
    }
}

inline void merge_document(::rapidjson::Document& dest, ::rapidjson::Document& src)
{
    merge_object(dest, src, dest.GetAllocator());
}

}  // namespace ibis::support::rapidjson

namespace rapidjson {

inline void merge(Value& dest, Value& src, Document::AllocatorType& allocator)
{
    ::ibis::support::rapidjson::merge_object(dest, src, allocator);
}

inline void merge(Document& dest, Document& src)
{
    ::ibis::support::rapidjson::merge_document(dest, src);
}

}  // namespace rapidjson
