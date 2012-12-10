/* Generated by the protocol buffer compiler.  DO NOT EDIT! */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C_NO_DEPRECATED
#define PROTOBUF_C_NO_DEPRECATED
#endif

#include "msg.pb-c.h"
void   doozer__request__init
                     (Doozer__Request         *message)
{
  static Doozer__Request init_value = DOOZER__REQUEST__INIT;
  *message = init_value;
}
size_t doozer__request__get_packed_size
                     (const Doozer__Request *message)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &doozer__request__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t doozer__request__pack
                     (const Doozer__Request *message,
                      uint8_t       *out)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &doozer__request__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t doozer__request__pack_to_buffer
                     (const Doozer__Request *message,
                      ProtobufCBuffer *buffer)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &doozer__request__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Doozer__Request *
       doozer__request__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Doozer__Request *)
     protobuf_c_message_unpack (&doozer__request__descriptor,
                                allocator, len, data);
}
void   doozer__request__free_unpacked
                     (Doozer__Request *message,
                      ProtobufCAllocator *allocator)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &doozer__request__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   doozer__response__init
                     (Doozer__Response         *message)
{
  static Doozer__Response init_value = DOOZER__RESPONSE__INIT;
  *message = init_value;
}
size_t doozer__response__get_packed_size
                     (const Doozer__Response *message)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &doozer__response__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t doozer__response__pack
                     (const Doozer__Response *message,
                      uint8_t       *out)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &doozer__response__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t doozer__response__pack_to_buffer
                     (const Doozer__Response *message,
                      ProtobufCBuffer *buffer)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &doozer__response__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Doozer__Response *
       doozer__response__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Doozer__Response *)
     protobuf_c_message_unpack (&doozer__response__descriptor,
                                allocator, len, data);
}
void   doozer__response__free_unpacked
                     (Doozer__Response *message,
                      ProtobufCAllocator *allocator)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &doozer__response__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
const ProtobufCEnumValue doozer__request__verb__enum_values_by_number[10] =
{
  { "GET", "DOOZER__REQUEST__VERB__GET", 1 },
  { "SET", "DOOZER__REQUEST__VERB__SET", 2 },
  { "DEL", "DOOZER__REQUEST__VERB__DEL", 3 },
  { "REV", "DOOZER__REQUEST__VERB__REV", 5 },
  { "WAIT", "DOOZER__REQUEST__VERB__WAIT", 6 },
  { "NOP", "DOOZER__REQUEST__VERB__NOP", 7 },
  { "WALK", "DOOZER__REQUEST__VERB__WALK", 9 },
  { "GETDIR", "DOOZER__REQUEST__VERB__GETDIR", 14 },
  { "STAT", "DOOZER__REQUEST__VERB__STAT", 16 },
  { "ACCESS", "DOOZER__REQUEST__VERB__ACCESS", 99 },
};
static const ProtobufCIntRange doozer__request__verb__value_ranges[] = {
{1, 0},{5, 3},{9, 6},{14, 7},{16, 8},{99, 9},{0, 10}
};
const ProtobufCEnumValueIndex doozer__request__verb__enum_values_by_name[10] =
{
  { "ACCESS", 9 },
  { "DEL", 2 },
  { "GET", 0 },
  { "GETDIR", 7 },
  { "NOP", 5 },
  { "REV", 3 },
  { "SET", 1 },
  { "STAT", 8 },
  { "WAIT", 4 },
  { "WALK", 6 },
};
const ProtobufCEnumDescriptor doozer__request__verb__descriptor =
{
  PROTOBUF_C_ENUM_DESCRIPTOR_MAGIC,
  "doozer.Request.Verb",
  "Verb",
  "Doozer__Request__Verb",
  "doozer",
  10,
  doozer__request__verb__enum_values_by_number,
  10,
  doozer__request__verb__enum_values_by_name,
  6,
  doozer__request__verb__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
static const ProtobufCFieldDescriptor doozer__request__field_descriptors[7] =
{
  {
    "tag",
    1,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    PROTOBUF_C_OFFSETOF(Doozer__Request, has_tag),
    PROTOBUF_C_OFFSETOF(Doozer__Request, tag),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "verb",
    2,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_ENUM,
    PROTOBUF_C_OFFSETOF(Doozer__Request, has_verb),
    PROTOBUF_C_OFFSETOF(Doozer__Request, verb),
    &doozer__request__verb__descriptor,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "path",
    4,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    PROTOBUF_C_OFFSETOF(Doozer__Request, path),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "value",
    5,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_BYTES,
    PROTOBUF_C_OFFSETOF(Doozer__Request, has_value),
    PROTOBUF_C_OFFSETOF(Doozer__Request, value),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "other_tag",
    6,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    PROTOBUF_C_OFFSETOF(Doozer__Request, has_other_tag),
    PROTOBUF_C_OFFSETOF(Doozer__Request, other_tag),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "offset",
    7,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    PROTOBUF_C_OFFSETOF(Doozer__Request, has_offset),
    PROTOBUF_C_OFFSETOF(Doozer__Request, offset),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "rev",
    9,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT64,
    PROTOBUF_C_OFFSETOF(Doozer__Request, has_rev),
    PROTOBUF_C_OFFSETOF(Doozer__Request, rev),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned doozer__request__field_indices_by_name[] = {
  5,   /* field[5] = offset */
  4,   /* field[4] = other_tag */
  2,   /* field[2] = path */
  6,   /* field[6] = rev */
  0,   /* field[0] = tag */
  3,   /* field[3] = value */
  1,   /* field[1] = verb */
};
static const ProtobufCIntRange doozer__request__number_ranges[3 + 1] =
{
  { 1, 0 },
  { 4, 2 },
  { 9, 6 },
  { 0, 7 }
};
const ProtobufCMessageDescriptor doozer__request__descriptor =
{
  PROTOBUF_C_MESSAGE_DESCRIPTOR_MAGIC,
  "doozer.Request",
  "Request",
  "Doozer__Request",
  "doozer",
  sizeof(Doozer__Request),
  7,
  doozer__request__field_descriptors,
  doozer__request__field_indices_by_name,
  3,  doozer__request__number_ranges,
  (ProtobufCMessageInit) doozer__request__init,
  NULL,NULL,NULL    /* reserved[123] */
};
const ProtobufCEnumValue doozer__response__err__enum_values_by_number[12] =
{
  { "TAG_IN_USE", "DOOZER__RESPONSE__ERR__TAG_IN_USE", 1 },
  { "UNKNOWN_VERB", "DOOZER__RESPONSE__ERR__UNKNOWN_VERB", 2 },
  { "READONLY", "DOOZER__RESPONSE__ERR__READONLY", 3 },
  { "TOO_LATE", "DOOZER__RESPONSE__ERR__TOO_LATE", 4 },
  { "REV_MISMATCH", "DOOZER__RESPONSE__ERR__REV_MISMATCH", 5 },
  { "BAD_PATH", "DOOZER__RESPONSE__ERR__BAD_PATH", 6 },
  { "MISSING_ARG", "DOOZER__RESPONSE__ERR__MISSING_ARG", 7 },
  { "RANGE", "DOOZER__RESPONSE__ERR__RANGE", 8 },
  { "NOTDIR", "DOOZER__RESPONSE__ERR__NOTDIR", 20 },
  { "ISDIR", "DOOZER__RESPONSE__ERR__ISDIR", 21 },
  { "NOENT", "DOOZER__RESPONSE__ERR__NOENT", 22 },
  { "OTHER", "DOOZER__RESPONSE__ERR__OTHER", 127 },
};
static const ProtobufCIntRange doozer__response__err__value_ranges[] = {
{1, 0},{20, 8},{127, 11},{0, 12}
};
const ProtobufCEnumValueIndex doozer__response__err__enum_values_by_name[12] =
{
  { "BAD_PATH", 5 },
  { "ISDIR", 9 },
  { "MISSING_ARG", 6 },
  { "NOENT", 10 },
  { "NOTDIR", 8 },
  { "OTHER", 11 },
  { "RANGE", 7 },
  { "READONLY", 2 },
  { "REV_MISMATCH", 4 },
  { "TAG_IN_USE", 0 },
  { "TOO_LATE", 3 },
  { "UNKNOWN_VERB", 1 },
};
const ProtobufCEnumDescriptor doozer__response__err__descriptor =
{
  PROTOBUF_C_ENUM_DESCRIPTOR_MAGIC,
  "doozer.Response.Err",
  "Err",
  "Doozer__Response__Err",
  "doozer",
  12,
  doozer__response__err__enum_values_by_number,
  12,
  doozer__response__err__enum_values_by_name,
  3,
  doozer__response__err__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
static const ProtobufCFieldDescriptor doozer__response__field_descriptors[8] =
{
  {
    "tag",
    1,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    PROTOBUF_C_OFFSETOF(Doozer__Response, has_tag),
    PROTOBUF_C_OFFSETOF(Doozer__Response, tag),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "flags",
    2,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    PROTOBUF_C_OFFSETOF(Doozer__Response, has_flags),
    PROTOBUF_C_OFFSETOF(Doozer__Response, flags),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "rev",
    3,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT64,
    PROTOBUF_C_OFFSETOF(Doozer__Response, has_rev),
    PROTOBUF_C_OFFSETOF(Doozer__Response, rev),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "path",
    5,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    PROTOBUF_C_OFFSETOF(Doozer__Response, path),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "value",
    6,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_BYTES,
    PROTOBUF_C_OFFSETOF(Doozer__Response, has_value),
    PROTOBUF_C_OFFSETOF(Doozer__Response, value),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "len",
    8,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    PROTOBUF_C_OFFSETOF(Doozer__Response, has_len),
    PROTOBUF_C_OFFSETOF(Doozer__Response, len),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "err_code",
    100,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_ENUM,
    PROTOBUF_C_OFFSETOF(Doozer__Response, has_err_code),
    PROTOBUF_C_OFFSETOF(Doozer__Response, err_code),
    &doozer__response__err__descriptor,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "err_detail",
    101,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    PROTOBUF_C_OFFSETOF(Doozer__Response, err_detail),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned doozer__response__field_indices_by_name[] = {
  6,   /* field[6] = err_code */
  7,   /* field[7] = err_detail */
  1,   /* field[1] = flags */
  5,   /* field[5] = len */
  3,   /* field[3] = path */
  2,   /* field[2] = rev */
  0,   /* field[0] = tag */
  4,   /* field[4] = value */
};
static const ProtobufCIntRange doozer__response__number_ranges[4 + 1] =
{
  { 1, 0 },
  { 5, 3 },
  { 8, 5 },
  { 100, 6 },
  { 0, 8 }
};
const ProtobufCMessageDescriptor doozer__response__descriptor =
{
  PROTOBUF_C_MESSAGE_DESCRIPTOR_MAGIC,
  "doozer.Response",
  "Response",
  "Doozer__Response",
  "doozer",
  sizeof(Doozer__Response),
  8,
  doozer__response__field_descriptors,
  doozer__response__field_indices_by_name,
  4,  doozer__response__number_ranges,
  (ProtobufCMessageInit) doozer__response__init,
  NULL,NULL,NULL    /* reserved[123] */
};