// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ssl_decision.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "ssl_decision.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* ssl_decision_packet_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ssl_decision_packet_reflection_ = NULL;
const ::google::protobuf::Descriptor* ssl_decision_packet_Robot_Role_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ssl_decision_packet_Robot_Role_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* ssl_decision_packet_Color_descriptor_ = NULL;
const ::google::protobuf::EnumDescriptor* ssl_decision_packet_Side_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_ssl_5fdecision_2eproto() {
  protobuf_AddDesc_ssl_5fdecision_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "ssl_decision.proto");
  GOOGLE_CHECK(file != NULL);
  ssl_decision_packet_descriptor_ = file->message_type(0);
  static const int ssl_decision_packet_offsets_[5] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ssl_decision_packet, our_color_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ssl_decision_packet, our_side_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ssl_decision_packet, strategy_name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ssl_decision_packet, robot_roles_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ssl_decision_packet, comment_),
  };
  ssl_decision_packet_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ssl_decision_packet_descriptor_,
      ssl_decision_packet::default_instance_,
      ssl_decision_packet_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ssl_decision_packet, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ssl_decision_packet, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ssl_decision_packet));
  ssl_decision_packet_Robot_Role_descriptor_ = ssl_decision_packet_descriptor_->nested_type(0);
  static const int ssl_decision_packet_Robot_Role_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ssl_decision_packet_Robot_Role, robot_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ssl_decision_packet_Robot_Role, current_role_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ssl_decision_packet_Robot_Role, current_skill_),
  };
  ssl_decision_packet_Robot_Role_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ssl_decision_packet_Robot_Role_descriptor_,
      ssl_decision_packet_Robot_Role::default_instance_,
      ssl_decision_packet_Robot_Role_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ssl_decision_packet_Robot_Role, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ssl_decision_packet_Robot_Role, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ssl_decision_packet_Robot_Role));
  ssl_decision_packet_Color_descriptor_ = ssl_decision_packet_descriptor_->enum_type(0);
  ssl_decision_packet_Side_descriptor_ = ssl_decision_packet_descriptor_->enum_type(1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_ssl_5fdecision_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ssl_decision_packet_descriptor_, &ssl_decision_packet::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ssl_decision_packet_Robot_Role_descriptor_, &ssl_decision_packet_Robot_Role::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_ssl_5fdecision_2eproto() {
  delete ssl_decision_packet::default_instance_;
  delete ssl_decision_packet_reflection_;
  delete ssl_decision_packet_Robot_Role::default_instance_;
  delete ssl_decision_packet_Robot_Role_reflection_;
}

void protobuf_AddDesc_ssl_5fdecision_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\022ssl_decision.proto\"\341\002\n\023ssl_decision_pa"
    "cket\022-\n\tour_color\030\001 \002(\0162\032.ssl_decision_p"
    "acket.Color\022+\n\010our_side\030\002 \002(\0162\031.ssl_deci"
    "sion_packet.Side\022\025\n\rstrategy_name\030\003 \002(\t\022"
    "4\n\013robot_roles\030\004 \003(\0132\037.ssl_decision_pack"
    "et.Robot_Role\022\017\n\007comment\030\005 \001(\t\032K\n\nRobot_"
    "Role\022\020\n\010robot_id\030\001 \002(\r\022\024\n\014current_role\030\002"
    " \002(\t\022\025\n\rcurrent_skill\030\003 \002(\t\"\035\n\005Color\022\010\n\004"
    "blue\020\000\022\n\n\006yellow\020\001\"$\n\004Side\022\021\n\004left\020\377\377\377\377\377"
    "\377\377\377\377\001\022\t\n\005right\020\001", 376);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "ssl_decision.proto", &protobuf_RegisterTypes);
  ssl_decision_packet::default_instance_ = new ssl_decision_packet();
  ssl_decision_packet_Robot_Role::default_instance_ = new ssl_decision_packet_Robot_Role();
  ssl_decision_packet::default_instance_->InitAsDefaultInstance();
  ssl_decision_packet_Robot_Role::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_ssl_5fdecision_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_ssl_5fdecision_2eproto {
  StaticDescriptorInitializer_ssl_5fdecision_2eproto() {
    protobuf_AddDesc_ssl_5fdecision_2eproto();
  }
} static_descriptor_initializer_ssl_5fdecision_2eproto_;

// ===================================================================

const ::google::protobuf::EnumDescriptor* ssl_decision_packet_Color_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ssl_decision_packet_Color_descriptor_;
}
bool ssl_decision_packet_Color_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const ssl_decision_packet_Color ssl_decision_packet::blue;
const ssl_decision_packet_Color ssl_decision_packet::yellow;
const ssl_decision_packet_Color ssl_decision_packet::Color_MIN;
const ssl_decision_packet_Color ssl_decision_packet::Color_MAX;
const int ssl_decision_packet::Color_ARRAYSIZE;
#endif  // _MSC_VER
const ::google::protobuf::EnumDescriptor* ssl_decision_packet_Side_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ssl_decision_packet_Side_descriptor_;
}
bool ssl_decision_packet_Side_IsValid(int value) {
  switch(value) {
    case -1:
    case 1:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const ssl_decision_packet_Side ssl_decision_packet::left;
const ssl_decision_packet_Side ssl_decision_packet::right;
const ssl_decision_packet_Side ssl_decision_packet::Side_MIN;
const ssl_decision_packet_Side ssl_decision_packet::Side_MAX;
const int ssl_decision_packet::Side_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int ssl_decision_packet_Robot_Role::kRobotIdFieldNumber;
const int ssl_decision_packet_Robot_Role::kCurrentRoleFieldNumber;
const int ssl_decision_packet_Robot_Role::kCurrentSkillFieldNumber;
#endif  // !_MSC_VER

ssl_decision_packet_Robot_Role::ssl_decision_packet_Robot_Role()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void ssl_decision_packet_Robot_Role::InitAsDefaultInstance() {
}

ssl_decision_packet_Robot_Role::ssl_decision_packet_Robot_Role(const ssl_decision_packet_Robot_Role& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void ssl_decision_packet_Robot_Role::SharedCtor() {
  _cached_size_ = 0;
  robot_id_ = 0u;
  current_role_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  current_skill_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ssl_decision_packet_Robot_Role::~ssl_decision_packet_Robot_Role() {
  SharedDtor();
}

void ssl_decision_packet_Robot_Role::SharedDtor() {
  if (current_role_ != &::google::protobuf::internal::kEmptyString) {
    delete current_role_;
  }
  if (current_skill_ != &::google::protobuf::internal::kEmptyString) {
    delete current_skill_;
  }
  if (this != default_instance_) {
  }
}

void ssl_decision_packet_Robot_Role::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ssl_decision_packet_Robot_Role::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ssl_decision_packet_Robot_Role_descriptor_;
}

const ssl_decision_packet_Robot_Role& ssl_decision_packet_Robot_Role::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ssl_5fdecision_2eproto();
  return *default_instance_;
}

ssl_decision_packet_Robot_Role* ssl_decision_packet_Robot_Role::default_instance_ = NULL;

ssl_decision_packet_Robot_Role* ssl_decision_packet_Robot_Role::New() const {
  return new ssl_decision_packet_Robot_Role;
}

void ssl_decision_packet_Robot_Role::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    robot_id_ = 0u;
    if (has_current_role()) {
      if (current_role_ != &::google::protobuf::internal::kEmptyString) {
        current_role_->clear();
      }
    }
    if (has_current_skill()) {
      if (current_skill_ != &::google::protobuf::internal::kEmptyString) {
        current_skill_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ssl_decision_packet_Robot_Role::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 robot_id = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &robot_id_)));
          set_has_robot_id();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_current_role;
        break;
      }

      // required string current_role = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_current_role:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_current_role()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->current_role().data(), this->current_role().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_current_skill;
        break;
      }

      // required string current_skill = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_current_skill:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_current_skill()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->current_skill().data(), this->current_skill().length(),
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

void ssl_decision_packet_Robot_Role::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required uint32 robot_id = 1;
  if (has_robot_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->robot_id(), output);
  }

  // required string current_role = 2;
  if (has_current_role()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->current_role().data(), this->current_role().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->current_role(), output);
  }

  // required string current_skill = 3;
  if (has_current_skill()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->current_skill().data(), this->current_skill().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      3, this->current_skill(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* ssl_decision_packet_Robot_Role::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required uint32 robot_id = 1;
  if (has_robot_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->robot_id(), target);
  }

  // required string current_role = 2;
  if (has_current_role()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->current_role().data(), this->current_role().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->current_role(), target);
  }

  // required string current_skill = 3;
  if (has_current_skill()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->current_skill().data(), this->current_skill().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->current_skill(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int ssl_decision_packet_Robot_Role::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 robot_id = 1;
    if (has_robot_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->robot_id());
    }

    // required string current_role = 2;
    if (has_current_role()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->current_role());
    }

    // required string current_skill = 3;
    if (has_current_skill()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->current_skill());
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

void ssl_decision_packet_Robot_Role::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ssl_decision_packet_Robot_Role* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ssl_decision_packet_Robot_Role*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ssl_decision_packet_Robot_Role::MergeFrom(const ssl_decision_packet_Robot_Role& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_robot_id()) {
      set_robot_id(from.robot_id());
    }
    if (from.has_current_role()) {
      set_current_role(from.current_role());
    }
    if (from.has_current_skill()) {
      set_current_skill(from.current_skill());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ssl_decision_packet_Robot_Role::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ssl_decision_packet_Robot_Role::CopyFrom(const ssl_decision_packet_Robot_Role& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ssl_decision_packet_Robot_Role::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;

  return true;
}

void ssl_decision_packet_Robot_Role::Swap(ssl_decision_packet_Robot_Role* other) {
  if (other != this) {
    std::swap(robot_id_, other->robot_id_);
    std::swap(current_role_, other->current_role_);
    std::swap(current_skill_, other->current_skill_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ssl_decision_packet_Robot_Role::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ssl_decision_packet_Robot_Role_descriptor_;
  metadata.reflection = ssl_decision_packet_Robot_Role_reflection_;
  return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int ssl_decision_packet::kOurColorFieldNumber;
const int ssl_decision_packet::kOurSideFieldNumber;
const int ssl_decision_packet::kStrategyNameFieldNumber;
const int ssl_decision_packet::kRobotRolesFieldNumber;
const int ssl_decision_packet::kCommentFieldNumber;
#endif  // !_MSC_VER

ssl_decision_packet::ssl_decision_packet()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void ssl_decision_packet::InitAsDefaultInstance() {
}

ssl_decision_packet::ssl_decision_packet(const ssl_decision_packet& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void ssl_decision_packet::SharedCtor() {
  _cached_size_ = 0;
  our_color_ = 0;
  our_side_ = -1;
  strategy_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  comment_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ssl_decision_packet::~ssl_decision_packet() {
  SharedDtor();
}

void ssl_decision_packet::SharedDtor() {
  if (strategy_name_ != &::google::protobuf::internal::kEmptyString) {
    delete strategy_name_;
  }
  if (comment_ != &::google::protobuf::internal::kEmptyString) {
    delete comment_;
  }
  if (this != default_instance_) {
  }
}

void ssl_decision_packet::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ssl_decision_packet::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ssl_decision_packet_descriptor_;
}

const ssl_decision_packet& ssl_decision_packet::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ssl_5fdecision_2eproto();
  return *default_instance_;
}

ssl_decision_packet* ssl_decision_packet::default_instance_ = NULL;

ssl_decision_packet* ssl_decision_packet::New() const {
  return new ssl_decision_packet;
}

void ssl_decision_packet::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    our_color_ = 0;
    our_side_ = -1;
    if (has_strategy_name()) {
      if (strategy_name_ != &::google::protobuf::internal::kEmptyString) {
        strategy_name_->clear();
      }
    }
    if (has_comment()) {
      if (comment_ != &::google::protobuf::internal::kEmptyString) {
        comment_->clear();
      }
    }
  }
  robot_roles_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ssl_decision_packet::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .ssl_decision_packet.Color our_color = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::ssl_decision_packet_Color_IsValid(value)) {
            set_our_color(static_cast< ::ssl_decision_packet_Color >(value));
          } else {
            mutable_unknown_fields()->AddVarint(1, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_our_side;
        break;
      }

      // required .ssl_decision_packet.Side our_side = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_our_side:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::ssl_decision_packet_Side_IsValid(value)) {
            set_our_side(static_cast< ::ssl_decision_packet_Side >(value));
          } else {
            mutable_unknown_fields()->AddVarint(2, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_strategy_name;
        break;
      }

      // required string strategy_name = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_strategy_name:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_strategy_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->strategy_name().data(), this->strategy_name().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_robot_roles;
        break;
      }

      // repeated .ssl_decision_packet.Robot_Role robot_roles = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_robot_roles:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_robot_roles()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_robot_roles;
        if (input->ExpectTag(42)) goto parse_comment;
        break;
      }

      // optional string comment = 5;
      case 5: {
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

void ssl_decision_packet::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required .ssl_decision_packet.Color our_color = 1;
  if (has_our_color()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->our_color(), output);
  }

  // required .ssl_decision_packet.Side our_side = 2;
  if (has_our_side()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      2, this->our_side(), output);
  }

  // required string strategy_name = 3;
  if (has_strategy_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->strategy_name().data(), this->strategy_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      3, this->strategy_name(), output);
  }

  // repeated .ssl_decision_packet.Robot_Role robot_roles = 4;
  for (int i = 0; i < this->robot_roles_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      4, this->robot_roles(i), output);
  }

  // optional string comment = 5;
  if (has_comment()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->comment().data(), this->comment().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      5, this->comment(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* ssl_decision_packet::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required .ssl_decision_packet.Color our_color = 1;
  if (has_our_color()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->our_color(), target);
  }

  // required .ssl_decision_packet.Side our_side = 2;
  if (has_our_side()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      2, this->our_side(), target);
  }

  // required string strategy_name = 3;
  if (has_strategy_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->strategy_name().data(), this->strategy_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->strategy_name(), target);
  }

  // repeated .ssl_decision_packet.Robot_Role robot_roles = 4;
  for (int i = 0; i < this->robot_roles_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        4, this->robot_roles(i), target);
  }

  // optional string comment = 5;
  if (has_comment()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->comment().data(), this->comment().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        5, this->comment(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int ssl_decision_packet::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required .ssl_decision_packet.Color our_color = 1;
    if (has_our_color()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->our_color());
    }

    // required .ssl_decision_packet.Side our_side = 2;
    if (has_our_side()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->our_side());
    }

    // required string strategy_name = 3;
    if (has_strategy_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->strategy_name());
    }

    // optional string comment = 5;
    if (has_comment()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->comment());
    }

  }
  // repeated .ssl_decision_packet.Robot_Role robot_roles = 4;
  total_size += 1 * this->robot_roles_size();
  for (int i = 0; i < this->robot_roles_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->robot_roles(i));
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

void ssl_decision_packet::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ssl_decision_packet* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ssl_decision_packet*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ssl_decision_packet::MergeFrom(const ssl_decision_packet& from) {
  GOOGLE_CHECK_NE(&from, this);
  robot_roles_.MergeFrom(from.robot_roles_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_our_color()) {
      set_our_color(from.our_color());
    }
    if (from.has_our_side()) {
      set_our_side(from.our_side());
    }
    if (from.has_strategy_name()) {
      set_strategy_name(from.strategy_name());
    }
    if (from.has_comment()) {
      set_comment(from.comment());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ssl_decision_packet::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ssl_decision_packet::CopyFrom(const ssl_decision_packet& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ssl_decision_packet::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;

  for (int i = 0; i < robot_roles_size(); i++) {
    if (!this->robot_roles(i).IsInitialized()) return false;
  }
  return true;
}

void ssl_decision_packet::Swap(ssl_decision_packet* other) {
  if (other != this) {
    std::swap(our_color_, other->our_color_);
    std::swap(our_side_, other->our_side_);
    std::swap(strategy_name_, other->strategy_name_);
    robot_roles_.Swap(&other->robot_roles_);
    std::swap(comment_, other->comment_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ssl_decision_packet::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ssl_decision_packet_descriptor_;
  metadata.reflection = ssl_decision_packet_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
