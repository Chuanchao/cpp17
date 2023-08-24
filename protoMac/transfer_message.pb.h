// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: transfer_message.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_transfer_5fmessage_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_transfer_5fmessage_2eproto_2epb_2eh

#include <limits>
#include <string>
#include <type_traits>

#include "google/protobuf/port_def.inc"
#if PROTOBUF_VERSION < 4023000
#error "This file was generated by a newer version of protoc which is"
#error "incompatible with your Protocol Buffer headers. Please update"
#error "your headers."
#endif  // PROTOBUF_VERSION

#if 4023004 < PROTOBUF_MIN_PROTOC_VERSION
#error "This file was generated by an older version of protoc which is"
#error "incompatible with your Protocol Buffer headers. Please"
#error "regenerate this file with a newer version of protoc."
#endif  // PROTOBUF_MIN_PROTOC_VERSION
#include "google/protobuf/port_undef.inc"
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/generated_message_bases.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/message.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/unknown_field_set.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_transfer_5fmessage_2eproto

PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_transfer_5fmessage_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable
    descriptor_table_transfer_5fmessage_2eproto;
namespace transfer {
class ResponseEmptyMessage;
struct ResponseEmptyMessageDefaultTypeInternal;
extern ResponseEmptyMessageDefaultTypeInternal _ResponseEmptyMessage_default_instance_;
class TransferMessage;
struct TransferMessageDefaultTypeInternal;
extern TransferMessageDefaultTypeInternal _TransferMessage_default_instance_;
}  // namespace transfer
PROTOBUF_NAMESPACE_OPEN
template <>
::transfer::ResponseEmptyMessage* Arena::CreateMaybeMessage<::transfer::ResponseEmptyMessage>(Arena*);
template <>
::transfer::TransferMessage* Arena::CreateMaybeMessage<::transfer::TransferMessage>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

namespace transfer {

// ===================================================================


// -------------------------------------------------------------------

class ResponseEmptyMessage final :
    public ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase /* @@protoc_insertion_point(class_definition:transfer.ResponseEmptyMessage) */ {
 public:
  inline ResponseEmptyMessage() : ResponseEmptyMessage(nullptr) {}
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR ResponseEmptyMessage(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  ResponseEmptyMessage(const ResponseEmptyMessage& from);
  ResponseEmptyMessage(ResponseEmptyMessage&& from) noexcept
    : ResponseEmptyMessage() {
    *this = ::std::move(from);
  }

  inline ResponseEmptyMessage& operator=(const ResponseEmptyMessage& from) {
    CopyFrom(from);
    return *this;
  }
  inline ResponseEmptyMessage& operator=(ResponseEmptyMessage&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const ResponseEmptyMessage& default_instance() {
    return *internal_default_instance();
  }
  static inline const ResponseEmptyMessage* internal_default_instance() {
    return reinterpret_cast<const ResponseEmptyMessage*>(
               &_ResponseEmptyMessage_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(ResponseEmptyMessage& a, ResponseEmptyMessage& b) {
    a.Swap(&b);
  }
  inline void Swap(ResponseEmptyMessage* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(ResponseEmptyMessage* other) {
    if (other == this) return;
    ABSL_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  ResponseEmptyMessage* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<ResponseEmptyMessage>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::CopyFrom;
  inline void CopyFrom(const ResponseEmptyMessage& from) {
    ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::CopyImpl(*this, from);
  }
  using ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::MergeFrom;
  void MergeFrom(const ResponseEmptyMessage& from) {
    ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::MergeImpl(*this, from);
  }
  public:

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "transfer.ResponseEmptyMessage";
  }
  protected:
  explicit ResponseEmptyMessage(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:transfer.ResponseEmptyMessage)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
  };
  friend struct ::TableStruct_transfer_5fmessage_2eproto;
};// -------------------------------------------------------------------

class TransferMessage final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:transfer.TransferMessage) */ {
 public:
  inline TransferMessage() : TransferMessage(nullptr) {}
  ~TransferMessage() override;
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR TransferMessage(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  TransferMessage(const TransferMessage& from);
  TransferMessage(TransferMessage&& from) noexcept
    : TransferMessage() {
    *this = ::std::move(from);
  }

  inline TransferMessage& operator=(const TransferMessage& from) {
    CopyFrom(from);
    return *this;
  }
  inline TransferMessage& operator=(TransferMessage&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const TransferMessage& default_instance() {
    return *internal_default_instance();
  }
  static inline const TransferMessage* internal_default_instance() {
    return reinterpret_cast<const TransferMessage*>(
               &_TransferMessage_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(TransferMessage& a, TransferMessage& b) {
    a.Swap(&b);
  }
  inline void Swap(TransferMessage* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(TransferMessage* other) {
    if (other == this) return;
    ABSL_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  TransferMessage* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<TransferMessage>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const TransferMessage& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const TransferMessage& from) {
    TransferMessage::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(TransferMessage* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "transfer.TransferMessage";
  }
  protected:
  explicit TransferMessage(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kMessageNameFieldNumber = 1,
    kMessageContentFieldNumber = 2,
  };
  // string message_name = 1;
  void clear_message_name() ;
  const std::string& message_name() const;




  template <typename Arg_ = const std::string&, typename... Args_>
  void set_message_name(Arg_&& arg, Args_... args);
  std::string* mutable_message_name();
  PROTOBUF_NODISCARD std::string* release_message_name();
  void set_allocated_message_name(std::string* ptr);

  private:
  const std::string& _internal_message_name() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_message_name(
      const std::string& value);
  std::string* _internal_mutable_message_name();

  public:
  // bytes message_content = 2;
  void clear_message_content() ;
  const std::string& message_content() const;




  template <typename Arg_ = const std::string&, typename... Args_>
  void set_message_content(Arg_&& arg, Args_... args);
  std::string* mutable_message_content();
  PROTOBUF_NODISCARD std::string* release_message_content();
  void set_allocated_message_content(std::string* ptr);

  private:
  const std::string& _internal_message_content() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_message_content(
      const std::string& value);
  std::string* _internal_mutable_message_content();

  public:
  // @@protoc_insertion_point(class_scope:transfer.TransferMessage)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr message_name_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr message_content_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_transfer_5fmessage_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// ResponseEmptyMessage

// -------------------------------------------------------------------

// TransferMessage

// string message_name = 1;
inline void TransferMessage::clear_message_name() {
  _impl_.message_name_.ClearToEmpty();
}
inline const std::string& TransferMessage::message_name() const {
  // @@protoc_insertion_point(field_get:transfer.TransferMessage.message_name)
  return _internal_message_name();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void TransferMessage::set_message_name(Arg_&& arg,
                                                     Args_... args) {
  ;
  _impl_.message_name_.Set(static_cast<Arg_&&>(arg), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:transfer.TransferMessage.message_name)
}
inline std::string* TransferMessage::mutable_message_name() {
  std::string* _s = _internal_mutable_message_name();
  // @@protoc_insertion_point(field_mutable:transfer.TransferMessage.message_name)
  return _s;
}
inline const std::string& TransferMessage::_internal_message_name() const {
  return _impl_.message_name_.Get();
}
inline void TransferMessage::_internal_set_message_name(const std::string& value) {
  ;


  _impl_.message_name_.Set(value, GetArenaForAllocation());
}
inline std::string* TransferMessage::_internal_mutable_message_name() {
  ;
  return _impl_.message_name_.Mutable( GetArenaForAllocation());
}
inline std::string* TransferMessage::release_message_name() {
  // @@protoc_insertion_point(field_release:transfer.TransferMessage.message_name)
  return _impl_.message_name_.Release();
}
inline void TransferMessage::set_allocated_message_name(std::string* value) {
  _impl_.message_name_.SetAllocated(value, GetArenaForAllocation());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.message_name_.IsDefault()) {
          _impl_.message_name_.Set("", GetArenaForAllocation());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:transfer.TransferMessage.message_name)
}

// bytes message_content = 2;
inline void TransferMessage::clear_message_content() {
  _impl_.message_content_.ClearToEmpty();
}
inline const std::string& TransferMessage::message_content() const {
  // @@protoc_insertion_point(field_get:transfer.TransferMessage.message_content)
  return _internal_message_content();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void TransferMessage::set_message_content(Arg_&& arg,
                                                     Args_... args) {
  ;
  _impl_.message_content_.SetBytes(static_cast<Arg_&&>(arg), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:transfer.TransferMessage.message_content)
}
inline std::string* TransferMessage::mutable_message_content() {
  std::string* _s = _internal_mutable_message_content();
  // @@protoc_insertion_point(field_mutable:transfer.TransferMessage.message_content)
  return _s;
}
inline const std::string& TransferMessage::_internal_message_content() const {
  return _impl_.message_content_.Get();
}
inline void TransferMessage::_internal_set_message_content(const std::string& value) {
  ;


  _impl_.message_content_.Set(value, GetArenaForAllocation());
}
inline std::string* TransferMessage::_internal_mutable_message_content() {
  ;
  return _impl_.message_content_.Mutable( GetArenaForAllocation());
}
inline std::string* TransferMessage::release_message_content() {
  // @@protoc_insertion_point(field_release:transfer.TransferMessage.message_content)
  return _impl_.message_content_.Release();
}
inline void TransferMessage::set_allocated_message_content(std::string* value) {
  _impl_.message_content_.SetAllocated(value, GetArenaForAllocation());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.message_content_.IsDefault()) {
          _impl_.message_content_.Set("", GetArenaForAllocation());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:transfer.TransferMessage.message_content)
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace transfer


// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_transfer_5fmessage_2eproto_2epb_2eh
