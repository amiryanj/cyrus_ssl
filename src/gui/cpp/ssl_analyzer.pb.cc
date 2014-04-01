// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "ssl_analyzer.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* ssl_analyzer_packet_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ssl_analyzer_packet_reflection_ = NULL;
const ::google::protobuf::Descriptor* ssl_analyzer_packet_RobotIntersectTime_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ssl_analyzer_packet_RobotIntersectTime_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* ssl_analyzer_packet_Color_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_ssl_5fanalyzer_2eproto() {
  protobuf_AddDesc_ssl_5fanalyzer_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "ssl_analyzer.proto");
  GOOGLE_CHECK(file != NULL);
  ssl_analyzer_packet_descriptor_ = file->message_type(0);
  static const int ssl_analyzer_packet_offsets_[7] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ssl_analyzer_packet, nearest_blue_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ssl_analyzer_packet, nearest_yellow_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ssl_analyzer_packet, possessor_team_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ssl_analyzer_packet, nearest_can_kick_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ssl_analyzer_packet, is_game_running_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ssl_analyzer_packet, intersects_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ssl_analyzer_packet, comment_),
  };
  ssl_analyzer_packet_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ssl_analyzer_packet_descriptor_,
      ssl_analyzer_packet::default_instance_,
      ssl_analyzer_packet_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ssl_analyzer_packet, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ssl_analyzer_packet, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ssl_analyzer_packet));
  ssl_analyzer_packet_RobotIntersectTime_descriptor_ = ssl_analyzer_packet_descriptor_->nested_type(0);
  static const int ssl_analyzer_packet_RobotIntersectTime_offsets_[5] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ssl_analyzer_packet_RobotIntersectTime, color_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ssl_analyzer_packet_RobotIntersectTime, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ssl_analyzer_packet_RobotIntersectTime, time_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ssl_analyzer_packet_RobotIntersectTime, intersect_x_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ssl_analyzer_packet_RobotIntersectTime, intersect_y_),
  };
  ssl_analyzer_packet_RobotIntersectTime_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ssl_analyzer_packet_RobotIntersectTime_descriptor_,
      ssl_analyzer_packet_RobotIntersectTime::default_instance_,
      ssl_analyzer_packet_RobotIntersectTime_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ssl_analyzer_packet_RobotIntersectTime, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ssl_analyzer_packet_RobotIntersectTime, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ssl_analyzer_packet_RobotIntersectTime));
  ssl_analyzer_packet_Color_descriptor_ = ssl_analyzer_packet_descriptor_->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_ssl_5fanalyzer_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ssl_analyzer_packet_descriptor_, &ssl_analyzer_packet::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ssl_analyzer_packet_RobotIntersectTime_descriptor_, &ssl_analyzer_packet_RobotIntersectTime::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_ssl_5fanalyzer_2eproto() {
  delete ssl_analyzer_packet::default_instance_;
  delete ssl_analyzer_packet_reflection_;
  delete ssl_analyzer_packet_RobotIntersectTime::default_instance_;
  delete ssl_analyzer_packet_RobotIntersectTime_reflection_;
}

void protobuf_AddDesc_ssl_5fanalyzer_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\022ssl_analyzer.proto\"\266\003\n\023ssl_analyzer_pa"
    "cket\022\027\n\017nearest_blue_id\030\001 \002(\r\022\031\n\021nearest"
    "_yellow_id\030\002 \002(\r\0222\n\016possessor_team\030\003 \002(\016"
    "2\032.ssl_analyzer_packet.Color\022\030\n\020nearest_"
    "can_kick\030\004 \002(\010\022\027\n\017is_game_running\030\005 \002(\010\022"
    ";\n\nintersects\030\006 \003(\0132\'.ssl_analyzer_packe"
    "t.RobotIntersectTime\022\017\n\007comment\030\007 \001(\t\032\203\001"
    "\n\022RobotIntersectTime\022)\n\005color\030\001 \002(\0162\032.ss"
    "l_analyzer_packet.Color\022\n\n\002id\030\002 \002(\r\022\014\n\004t"
    "ime\030\003 \002(\002\022\023\n\013intersect_x\030\004 \002(\002\022\023\n\013inters"
    "ect_y\030\005 \002(\002\"0\n\005Color\022\021\n\004none\020\377\377\377\377\377\377\377\377\377\001\022"
    "\010\n\004blue\020\000\022\n\n\006yellow\020\001", 461);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "ssl_analyzer.proto", &protobuf_RegisterTypes);
  ssl_analyzer_packet::default_instance_ = new ssl_analyzer_packet();
  ssl_analyzer_packet_RobotIntersectTime::default_instance_ = new ssl_analyzer_packet_RobotIntersectTime();
  ssl_analyzer_packet::default_instance_->InitAsDefaultInstance();
  ssl_analyzer_packet_RobotIntersectTime::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_ssl_5fanalyzer_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_ssl_5fanalyzer_2eproto {
  StaticDescriptorInitializer_ssl_5fanalyzer_2eproto() {
    protobuf_AddDesc_ssl_5fanalyzer_2eproto();
  }
} static_descriptor_initializer_ssl_5fanalyzer_2eproto_;


// ===================================================================

const ::google::protobuf::EnumDescriptor* ssl_analyzer_packet_Color_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ssl_analyzer_packet_Color_descriptor_;
}
bool ssl_analyzer_packet_Color_IsValid(int value) {
  switch(value) {
    case -1:
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const ssl_analyzer_packet_Color ssl_analyzer_packet::none;
const ssl_analyzer_packet_Color ssl_analyzer_packet::blue;
const ssl_analyzer_packet_Color ssl_analyzer_packet::yellow;
const ssl_analyzer_packet_Color ssl_analyzer_packet::Color_MIN;
const ssl_analyzer_packet_Color ssl_analyzer_packet::Color_MAX;
const int ssl_analyzer_packet::Color_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int ssl_analyzer_packet_RobotIntersectTime::kColorFieldNumber;
const int ssl_analyzer_packet_RobotIntersectTime::kIdFieldNumber;
const int ssl_analyzer_packet_RobotIntersectTime::kTimeFieldNumber;
const int ssl_analyzer_packet_RobotIntersectTime::kIntersectXFieldNumber;
const int ssl_analyzer_packet_RobotIntersectTime::kIntersectYFieldNumber;
#endif  // !_MSC_VER

ssl_analyzer_packet_RobotIntersectTime::ssl_analyzer_packet_RobotIntersectTime()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void ssl_analyzer_packet_RobotIntersectTime::InitAsDefaultInstance() {
}

ssl_analyzer_packet_RobotIntersectTime::ssl_analyzer_packet_RobotIntersectTime(const ssl_analyzer_packet_RobotIntersectTime& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void ssl_analyzer_packet_RobotIntersectTime::SharedCtor() {
  _cached_size_ = 0;
  color_ = -1;
  id_ = 0u;
  time_ = 0;
  intersect_x_ = 0;
  intersect_y_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ssl_analyzer_packet_RobotIntersectTime::~ssl_analyzer_packet_RobotIntersectTime() {
  SharedDtor();
}

void ssl_analyzer_packet_RobotIntersectTime::SharedDtor() {
  if (this != default_instance_) {
  }
}

void ssl_analyzer_packet_RobotIntersectTime::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ssl_analyzer_packet_RobotIntersectTime::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ssl_analyzer_packet_RobotIntersectTime_descriptor_;
}

const ssl_analyzer_packet_RobotIntersectTime& ssl_analyzer_packet_RobotIntersectTime::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ssl_5fanalyzer_2eproto();  return *default_instance_;
}

ssl_analyzer_packet_RobotIntersectTime* ssl_analyzer_packet_RobotIntersectTime::default_instance_ = NULL;

ssl_analyzer_packet_RobotIntersectTime* ssl_analyzer_packet_RobotIntersectTime::New() const {
  return new ssl_analyzer_packet_RobotIntersectTime;
}

void ssl_analyzer_packet_RobotIntersectTime::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    color_ = -1;
    id_ = 0u;
    time_ = 0;
    intersect_x_ = 0;
    intersect_y_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ssl_analyzer_packet_RobotIntersectTime::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .ssl_analyzer_packet.Color color = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::ssl_analyzer_packet_Color_IsValid(value)) {
            set_color(static_cast< ::ssl_analyzer_packet_Color >(value));
          } else {
            mutable_unknown_fields()->AddVarint(1, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_id;
        break;
      }
      
      // required uint32 id = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &id_)));
          set_has_id();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(29)) goto parse_time;
        break;
      }
      
      // required float time = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_time:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &time_)));
          set_has_time();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(37)) goto parse_intersect_x;
        break;
      }
      
      // required float intersect_x = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_intersect_x:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &intersect_x_)));
          set_has_intersect_x();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(45)) goto parse_intersect_y;
        break;
      }
      
      // required float intersect_y = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_intersect_y:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &intersect_y_)));
          set_has_intersect_y();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void ssl_analyzer_packet_RobotIntersectTime::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required .ssl_analyzer_packet.Color color = 1;
  if (has_color()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->color(), output);
  }
  
  // required uint32 id = 2;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->id(), output);
  }
  
  // required float time = 3;
  if (has_time()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(3, this->time(), output);
  }
  
  // required float intersect_x = 4;
  if (has_intersect_x()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(4, this->intersect_x(), output);
  }
  
  // required float intersect_y = 5;
  if (has_intersect_y()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(5, this->intersect_y(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* ssl_analyzer_packet_RobotIntersectTime::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required .ssl_analyzer_packet.Color color = 1;
  if (has_color()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->color(), target);
  }
  
  // required uint32 id = 2;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->id(), target);
  }
  
  // required float time = 3;
  if (has_time()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(3, this->time(), target);
  }
  
  // required float intersect_x = 4;
  if (has_intersect_x()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(4, this->intersect_x(), target);
  }
  
  // required float intersect_y = 5;
  if (has_intersect_y()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(5, this->intersect_y(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int ssl_analyzer_packet_RobotIntersectTime::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required .ssl_analyzer_packet.Color color = 1;
    if (has_color()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->color());
    }
    
    // required uint32 id = 2;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->id());
    }
    
    // required float time = 3;
    if (has_time()) {
      total_size += 1 + 4;
    }
    
    // required float intersect_x = 4;
    if (has_intersect_x()) {
      total_size += 1 + 4;
    }
    
    // required float intersect_y = 5;
    if (has_intersect_y()) {
      total_size += 1 + 4;
    }
    
  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ssl_analyzer_packet_RobotIntersectTime::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ssl_analyzer_packet_RobotIntersectTime* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ssl_analyzer_packet_RobotIntersectTime*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ssl_analyzer_packet_RobotIntersectTime::MergeFrom(const ssl_analyzer_packet_RobotIntersectTime& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_color()) {
      set_color(from.color());
    }
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_time()) {
      set_time(from.time());
    }
    if (from.has_intersect_x()) {
      set_intersect_x(from.intersect_x());
    }
    if (from.has_intersect_y()) {
      set_intersect_y(from.intersect_y());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ssl_analyzer_packet_RobotIntersectTime::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ssl_analyzer_packet_RobotIntersectTime::CopyFrom(const ssl_analyzer_packet_RobotIntersectTime& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ssl_analyzer_packet_RobotIntersectTime::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000001f) != 0x0000001f) return false;
  
  return true;
}

void ssl_analyzer_packet_RobotIntersectTime::Swap(ssl_analyzer_packet_RobotIntersectTime* other) {
  if (other != this) {
    std::swap(color_, other->color_);
    std::swap(id_, other->id_);
    std::swap(time_, other->time_);
    std::swap(intersect_x_, other->intersect_x_);
    std::swap(intersect_y_, other->intersect_y_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ssl_analyzer_packet_RobotIntersectTime::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ssl_analyzer_packet_RobotIntersectTime_descriptor_;
  metadata.reflection = ssl_analyzer_packet_RobotIntersectTime_reflection_;
  return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int ssl_analyzer_packet::kNearestBlueIdFieldNumber;
const int ssl_analyzer_packet::kNearestYellowIdFieldNumber;
const int ssl_analyzer_packet::kPossessorTeamFieldNumber;
const int ssl_analyzer_packet::kNearestCanKickFieldNumber;
const int ssl_analyzer_packet::kIsGameRunningFieldNumber;
const int ssl_analyzer_packet::kIntersectsFieldNumber;
const int ssl_analyzer_packet::kCommentFieldNumber;
#endif  // !_MSC_VER

ssl_analyzer_packet::ssl_analyzer_packet()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void ssl_analyzer_packet::InitAsDefaultInstance() {
}

ssl_analyzer_packet::ssl_analyzer_packet(const ssl_analyzer_packet& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void ssl_analyzer_packet::SharedCtor() {
  _cached_size_ = 0;
  nearest_blue_id_ = 0u;
  nearest_yellow_id_ = 0u;
  possessor_team_ = -1;
  nearest_can_kick_ = false;
  is_game_running_ = false;
  comment_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ssl_analyzer_packet::~ssl_analyzer_packet() {
  SharedDtor();
}

void ssl_analyzer_packet::SharedDtor() {
  if (comment_ != &::google::protobuf::internal::kEmptyString) {
    delete comment_;
  }
  if (this != default_instance_) {
  }
}

void ssl_analyzer_packet::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ssl_analyzer_packet::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ssl_analyzer_packet_descriptor_;
}

const ssl_analyzer_packet& ssl_analyzer_packet::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ssl_5fanalyzer_2eproto();  return *default_instance_;
}

ssl_analyzer_packet* ssl_analyzer_packet::default_instance_ = NULL;

ssl_analyzer_packet* ssl_analyzer_packet::New() const {
  return new ssl_analyzer_packet;
}

void ssl_analyzer_packet::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    nearest_blue_id_ = 0u;
    nearest_yellow_id_ = 0u;
    possessor_team_ = -1;
    nearest_can_kick_ = false;
    is_game_running_ = false;
    if (has_comment()) {
      if (comment_ != &::google::protobuf::internal::kEmptyString) {
        comment_->clear();
      }
    }
  }
  intersects_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ssl_analyzer_packet::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 nearest_blue_id = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &nearest_blue_id_)));
          set_has_nearest_blue_id();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_nearest_yellow_id;
        break;
      }
      
      // required uint32 nearest_yellow_id = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_nearest_yellow_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &nearest_yellow_id_)));
          set_has_nearest_yellow_id();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_possessor_team;
        break;
      }
      
      // required .ssl_analyzer_packet.Color possessor_team = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_possessor_team:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::ssl_analyzer_packet_Color_IsValid(value)) {
            set_possessor_team(static_cast< ::ssl_analyzer_packet_Color >(value));
          } else {
            mutable_unknown_fields()->AddVarint(3, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_nearest_can_kick;
        break;
      }
      
      // required bool nearest_can_kick = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_nearest_can_kick:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &nearest_can_kick_)));
          set_has_nearest_can_kick();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(40)) goto parse_is_game_running;
        break;
      }
      
      // required bool is_game_running = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_is_game_running:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &is_game_running_)));
          set_has_is_game_running();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(50)) goto parse_intersects;
        break;
      }
      
      // repeated .ssl_analyzer_packet.RobotIntersectTime intersects = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_intersects:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_intersects()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(50)) goto parse_intersects;
        if (input->ExpectTag(58)) goto parse_comment;
        break;
      }
      
      // optional string comment = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_comment:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_comment()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->comment().data(), this->comment().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void ssl_analyzer_packet::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required uint32 nearest_blue_id = 1;
  if (has_nearest_blue_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->nearest_blue_id(), output);
  }
  
  // required uint32 nearest_yellow_id = 2;
  if (has_nearest_yellow_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->nearest_yellow_id(), output);
  }
  
  // required .ssl_analyzer_packet.Color possessor_team = 3;
  if (has_possessor_team()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      3, this->possessor_team(), output);
  }
  
  // required bool nearest_can_kick = 4;
  if (has_nearest_can_kick()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(4, this->nearest_can_kick(), output);
  }
  
  // required bool is_game_running = 5;
  if (has_is_game_running()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(5, this->is_game_running(), output);
  }
  
  // repeated .ssl_analyzer_packet.RobotIntersectTime intersects = 6;
  for (int i = 0; i < this->intersects_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      6, this->intersects(i), output);
  }
  
  // optional string comment = 7;
  if (has_comment()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->comment().data(), this->comment().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      7, this->comment(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* ssl_analyzer_packet::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required uint32 nearest_blue_id = 1;
  if (has_nearest_blue_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->nearest_blue_id(), target);
  }
  
  // required uint32 nearest_yellow_id = 2;
  if (has_nearest_yellow_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->nearest_yellow_id(), target);
  }
  
  // required .ssl_analyzer_packet.Color possessor_team = 3;
  if (has_possessor_team()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      3, this->possessor_team(), target);
  }
  
  // required bool nearest_can_kick = 4;
  if (has_nearest_can_kick()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(4, this->nearest_can_kick(), target);
  }
  
  // required bool is_game_running = 5;
  if (has_is_game_running()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(5, this->is_game_running(), target);
  }
  
  // repeated .ssl_analyzer_packet.RobotIntersectTime intersects = 6;
  for (int i = 0; i < this->intersects_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        6, this->intersects(i), target);
  }
  
  // optional string comment = 7;
  if (has_comment()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->comment().data(), this->comment().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        7, this->comment(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int ssl_analyzer_packet::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 nearest_blue_id = 1;
    if (has_nearest_blue_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->nearest_blue_id());
    }
    
    // required uint32 nearest_yellow_id = 2;
    if (has_nearest_yellow_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->nearest_yellow_id());
    }
    
    // required .ssl_analyzer_packet.Color possessor_team = 3;
    if (has_possessor_team()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->possessor_team());
    }
    
    // required bool nearest_can_kick = 4;
    if (has_nearest_can_kick()) {
      total_size += 1 + 1;
    }
    
    // required bool is_game_running = 5;
    if (has_is_game_running()) {
      total_size += 1 + 1;
    }
    
    // optional string comment = 7;
    if (has_comment()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->comment());
    }
    
  }
  // repeated .ssl_analyzer_packet.RobotIntersectTime intersects = 6;
  total_size += 1 * this->intersects_size();
  for (int i = 0; i < this->intersects_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->intersects(i));
  }
  
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ssl_analyzer_packet::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ssl_analyzer_packet* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ssl_analyzer_packet*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ssl_analyzer_packet::MergeFrom(const ssl_analyzer_packet& from) {
  GOOGLE_CHECK_NE(&from, this);
  intersects_.MergeFrom(from.intersects_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_nearest_blue_id()) {
      set_nearest_blue_id(from.nearest_blue_id());
    }
    if (from.has_nearest_yellow_id()) {
      set_nearest_yellow_id(from.nearest_yellow_id());
    }
    if (from.has_possessor_team()) {
      set_possessor_team(from.possessor_team());
    }
    if (from.has_nearest_can_kick()) {
      set_nearest_can_kick(from.nearest_can_kick());
    }
    if (from.has_is_game_running()) {
      set_is_game_running(from.is_game_running());
    }
    if (from.has_comment()) {
      set_comment(from.comment());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ssl_analyzer_packet::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ssl_analyzer_packet::CopyFrom(const ssl_analyzer_packet& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ssl_analyzer_packet::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000001f) != 0x0000001f) return false;
  
  for (int i = 0; i < intersects_size(); i++) {
    if (!this->intersects(i).IsInitialized()) return false;
  }
  return true;
}

void ssl_analyzer_packet::Swap(ssl_analyzer_packet* other) {
  if (other != this) {
    std::swap(nearest_blue_id_, other->nearest_blue_id_);
    std::swap(nearest_yellow_id_, other->nearest_yellow_id_);
    std::swap(possessor_team_, other->possessor_team_);
    std::swap(nearest_can_kick_, other->nearest_can_kick_);
    std::swap(is_game_running_, other->is_game_running_);
    intersects_.Swap(&other->intersects_);
    std::swap(comment_, other->comment_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ssl_analyzer_packet::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ssl_analyzer_packet_descriptor_;
  metadata.reflection = ssl_analyzer_packet_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
