// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "message_plotter.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* Plotter_Packet_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Plotter_Packet_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_message_5fplotter_2eproto() {
  protobuf_AddDesc_message_5fplotter_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "message_plotter.proto");
  GOOGLE_CHECK(file != NULL);
  Plotter_Packet_descriptor_ = file->message_type(0);
  static const int Plotter_Packet_offsets_[6] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Plotter_Packet, name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Plotter_Packet, values_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Plotter_Packet, key_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Plotter_Packet, legends_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Plotter_Packet, clear_history_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Plotter_Packet, sender_name_),
  };
  Plotter_Packet_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Plotter_Packet_descriptor_,
      Plotter_Packet::default_instance_,
      Plotter_Packet_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Plotter_Packet, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Plotter_Packet, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Plotter_Packet));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_message_5fplotter_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Plotter_Packet_descriptor_, &Plotter_Packet::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_message_5fplotter_2eproto() {
  delete Plotter_Packet::default_instance_;
  delete Plotter_Packet_reflection_;
}

void protobuf_AddDesc_message_5fplotter_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\025message_plotter.proto\"x\n\016Plotter_Packe"
    "t\022\014\n\004name\030\001 \002(\t\022\016\n\006values\030\002 \003(\001\022\013\n\003key\030\003"
    " \001(\001\022\017\n\007legends\030\004 \003(\t\022\025\n\rclear_history\030\005"
    " \001(\010\022\023\n\013sender_name\030\006 \001(\t", 145);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "message_plotter.proto", &protobuf_RegisterTypes);
  Plotter_Packet::default_instance_ = new Plotter_Packet();
  Plotter_Packet::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_message_5fplotter_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_message_5fplotter_2eproto {
  StaticDescriptorInitializer_message_5fplotter_2eproto() {
    protobuf_AddDesc_message_5fplotter_2eproto();
  }
} static_descriptor_initializer_message_5fplotter_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int Plotter_Packet::kNameFieldNumber;
const int Plotter_Packet::kValuesFieldNumber;
const int Plotter_Packet::kKeyFieldNumber;
const int Plotter_Packet::kLegendsFieldNumber;
const int Plotter_Packet::kClearHistoryFieldNumber;
const int Plotter_Packet::kSenderNameFieldNumber;
#endif  // !_MSC_VER

Plotter_Packet::Plotter_Packet()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Plotter_Packet::InitAsDefaultInstance() {
}

Plotter_Packet::Plotter_Packet(const Plotter_Packet& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Plotter_Packet::SharedCtor() {
  _cached_size_ = 0;
  name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  key_ = 0;
  clear_history_ = false;
  sender_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Plotter_Packet::~Plotter_Packet() {
  SharedDtor();
}

void Plotter_Packet::SharedDtor() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    delete name_;
  }
  if (sender_name_ != &::google::protobuf::internal::kEmptyString) {
    delete sender_name_;
  }
  if (this != default_instance_) {
  }
}

void Plotter_Packet::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Plotter_Packet::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Plotter_Packet_descriptor_;
}

const Plotter_Packet& Plotter_Packet::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_message_5fplotter_2eproto();  return *default_instance_;
}

Plotter_Packet* Plotter_Packet::default_instance_ = NULL;

Plotter_Packet* Plotter_Packet::New() const {
  return new Plotter_Packet;
}

void Plotter_Packet::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_name()) {
      if (name_ != &::google::protobuf::internal::kEmptyString) {
        name_->clear();
      }
    }
    key_ = 0;
    clear_history_ = false;
    if (has_sender_name()) {
      if (sender_name_ != &::google::protobuf::internal::kEmptyString) {
        sender_name_->clear();
      }
    }
  }
  values_.Clear();
  legends_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Plotter_Packet::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string name = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->name().data(), this->name().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(17)) goto parse_values;
        break;
      }
      
      // repeated double values = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
         parse_values:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 1, 17, input, this->mutable_values())));
        } else if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag)
                   == ::google::protobuf::internal::WireFormatLite::
                      WIRETYPE_LENGTH_DELIMITED) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, this->mutable_values())));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(17)) goto parse_values;
        if (input->ExpectTag(25)) goto parse_key;
        break;
      }
      
      // optional double key = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
         parse_key:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &key_)));
          set_has_key();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_legends;
        break;
      }
      
      // repeated string legends = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_legends:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->add_legends()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->legends(0).data(), this->legends(0).length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_legends;
        if (input->ExpectTag(40)) goto parse_clear_history;
        break;
      }
      
      // optional bool clear_history = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_clear_history:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &clear_history_)));
          set_has_clear_history();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(50)) goto parse_sender_name;
        break;
      }
      
      // optional string sender_name = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_sender_name:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_sender_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->sender_name().data(), this->sender_name().length(),
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

void Plotter_Packet::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required string name = 1;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->name(), output);
  }
  
  // repeated double values = 2;
  for (int i = 0; i < this->values_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(
      2, this->values(i), output);
  }
  
  // optional double key = 3;
  if (has_key()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(3, this->key(), output);
  }
  
  // repeated string legends = 4;
  for (int i = 0; i < this->legends_size(); i++) {
  ::google::protobuf::internal::WireFormat::VerifyUTF8String(
    this->legends(i).data(), this->legends(i).length(),
    ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      4, this->legends(i), output);
  }
  
  // optional bool clear_history = 5;
  if (has_clear_history()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(5, this->clear_history(), output);
  }
  
  // optional string sender_name = 6;
  if (has_sender_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->sender_name().data(), this->sender_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      6, this->sender_name(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Plotter_Packet::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required string name = 1;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->name(), target);
  }
  
  // repeated double values = 2;
  for (int i = 0; i < this->values_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteDoubleToArray(2, this->values(i), target);
  }
  
  // optional double key = 3;
  if (has_key()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(3, this->key(), target);
  }
  
  // repeated string legends = 4;
  for (int i = 0; i < this->legends_size(); i++) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->legends(i).data(), this->legends(i).length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target = ::google::protobuf::internal::WireFormatLite::
      WriteStringToArray(4, this->legends(i), target);
  }
  
  // optional bool clear_history = 5;
  if (has_clear_history()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(5, this->clear_history(), target);
  }
  
  // optional string sender_name = 6;
  if (has_sender_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->sender_name().data(), this->sender_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        6, this->sender_name(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Plotter_Packet::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string name = 1;
    if (has_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->name());
    }
    
    // optional double key = 3;
    if (has_key()) {
      total_size += 1 + 8;
    }
    
    // optional bool clear_history = 5;
    if (has_clear_history()) {
      total_size += 1 + 1;
    }
    
    // optional string sender_name = 6;
    if (has_sender_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->sender_name());
    }
    
  }
  // repeated double values = 2;
  {
    int data_size = 0;
    data_size = 8 * this->values_size();
    total_size += 1 * this->values_size() + data_size;
  }
  
  // repeated string legends = 4;
  total_size += 1 * this->legends_size();
  for (int i = 0; i < this->legends_size(); i++) {
    total_size += ::google::protobuf::internal::WireFormatLite::StringSize(
      this->legends(i));
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

void Plotter_Packet::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Plotter_Packet* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Plotter_Packet*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Plotter_Packet::MergeFrom(const Plotter_Packet& from) {
  GOOGLE_CHECK_NE(&from, this);
  values_.MergeFrom(from.values_);
  legends_.MergeFrom(from.legends_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_name()) {
      set_name(from.name());
    }
    if (from.has_key()) {
      set_key(from.key());
    }
    if (from.has_clear_history()) {
      set_clear_history(from.clear_history());
    }
    if (from.has_sender_name()) {
      set_sender_name(from.sender_name());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Plotter_Packet::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Plotter_Packet::CopyFrom(const Plotter_Packet& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Plotter_Packet::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;
  
  return true;
}

void Plotter_Packet::Swap(Plotter_Packet* other) {
  if (other != this) {
    std::swap(name_, other->name_);
    values_.Swap(&other->values_);
    std::swap(key_, other->key_);
    legends_.Swap(&other->legends_);
    std::swap(clear_history_, other->clear_history_);
    std::swap(sender_name_, other->sender_name_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Plotter_Packet::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Plotter_Packet_descriptor_;
  metadata.reflection = Plotter_Packet_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)