# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: proto/packet.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='proto/packet.proto',
  package='',
  syntax='proto3',
  serialized_options=None,
  serialized_pb=_b('\n\x12proto/packet.proto\":\n\x06Packet\x12\x11\n\ttimestamp\x18\x01 \x01(\x04\x12\x0e\n\x06source\x18\x02 \x01(\t\x12\r\n\x05value\x18\x03 \x01(\x02\x62\x06proto3')
)




_PACKET = _descriptor.Descriptor(
  name='Packet',
  full_name='Packet',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='timestamp', full_name='Packet.timestamp', index=0,
      number=1, type=4, cpp_type=4, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='source', full_name='Packet.source', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='value', full_name='Packet.value', index=2,
      number=3, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=22,
  serialized_end=80,
)

DESCRIPTOR.message_types_by_name['Packet'] = _PACKET
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

Packet = _reflection.GeneratedProtocolMessageType('Packet', (_message.Message,), {
  'DESCRIPTOR' : _PACKET,
  '__module__' : 'proto.packet_pb2'
  # @@protoc_insertion_point(class_scope:Packet)
  })
_sym_db.RegisterMessage(Packet)


# @@protoc_insertion_point(module_scope)
