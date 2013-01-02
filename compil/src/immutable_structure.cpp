// Boost C++ Utility
#include <boost/assert.hpp>

#include "generator-test/immutable_structure.h"
// Standard C Library
#include <stddef.h>

int ImmutableStructure1::bitmask_r1()
{
    return 0x1;
}

int ImmutableStructure1::bitmask_o1()
{
    return 0x2;
}

int ImmutableStructure1::bitmask_d1()
{
    return 0x4;
}

int ImmutableStructure1::bitmask_s1()
{
    return 0x8;
}

ImmutableStructure1::Builder::Builder()
        : mpObject(new ImmutableStructure1())
{
}

ImmutableStructure1::Builder::Builder(const ImmutableStructure1& object)
        : mpObject(new ImmutableStructure1())
{
    *(ImmutableStructure1*)mpObject = object;
}

ImmutableStructure1::Builder::Builder(ImmutableStructure1RPtr pObject)
        : mpObject(pObject)
{
}

ImmutableStructure1::Builder::~Builder()
{
    delete (ImmutableStructure1RPtr)mpObject;
    mpObject = NULL;
}

const ImmutableStructure1& ImmutableStructure1::Builder::build() const
{
    BOOST_ASSERT(mpObject->isInitialized());
    return *(ImmutableStructure1RPtr)mpObject;
}

ImmutableStructure1SPtr ImmutableStructure1::Builder::finalize()
{
    BOOST_ASSERT(mpObject->isInitialized());
    ImmutableStructure1RPtr objectRPtr = (ImmutableStructure1RPtr)mpObject;
    mpObject = NULL;
    return ImmutableStructure1SPtr(objectRPtr);
}

ImmutableStructure1::ImmutableStructure1()
        : mBits(0)
        , mD1  (default_d1())
{
}

ImmutableStructure1::~ImmutableStructure1()
{
}

bool ImmutableStructure1::isInitialized() const
{
    if (!valid_r1()) return false;
    if (!valid_s1()) return false;
    return true;
}

long ImmutableStructure1::r1() const
{
    BOOST_ASSERT(valid_r1());
    return mR1;
}

bool ImmutableStructure1::valid_r1() const
{
    return (mBits & bitmask_r1()) != 0;
}

ImmutableStructure1::Builder& ImmutableStructure1::Builder::set_r1(long r1)
{
    mpObject->mR1    = r1;
    mpObject->mBits |= bitmask_r1();
    return *this;
}

void ImmutableStructure1::Builder::erase_r1()
{
    mpObject->mR1    =  0;
    mpObject->mBits &= ~bitmask_r1();
}

long ImmutableStructure1::o1() const
{
    BOOST_ASSERT(exist_o1());
    return mO1;
}

bool ImmutableStructure1::exist_o1() const
{
    return (mBits & bitmask_o1()) != 0;
}

ImmutableStructure1::Builder& ImmutableStructure1::Builder::set_o1(long o1)
{
    mpObject->mO1    = o1;
    mpObject->mBits |= bitmask_o1();
    return *this;
}

void ImmutableStructure1::Builder::clear_o1()
{
    mpObject->mO1    =  0;
    mpObject->mBits &= ~bitmask_o1();
}

long ImmutableStructure1::d1() const
{
    return mD1;
}

bool ImmutableStructure1::changed_d1() const
{
    return (mBits & bitmask_d1()) != 0;
}

long ImmutableStructure1::default_d1()
{
    return 1;
}

ImmutableStructure1::Builder& ImmutableStructure1::Builder::set_d1(long d1)
{
    mpObject->mD1    = d1;
    mpObject->mBits |= bitmask_d1();
    return *this;
}

ImmutableStructure1::Builder& ImmutableStructure1::Builder::update_d1(long d1)
{
    if (mpObject->default_d1() != d1)
        return set_d1(d1);

    reset_d1();
    return *this;
}

void ImmutableStructure1::Builder::reset_d1()
{
    mpObject->mD1    =  mpObject->default_d1();
    mpObject->mBits &= ~bitmask_d1          ();
}

const std::string& ImmutableStructure1::s1() const
{
    BOOST_ASSERT(valid_s1());
    return mS1;
}

bool ImmutableStructure1::valid_s1() const
{
    return (mBits & bitmask_s1()) != 0;
}

ImmutableStructure1::Builder& ImmutableStructure1::Builder::set_s1(const std::string& s1)
{
    mpObject->mS1    = s1;
    mpObject->mBits |= bitmask_s1();
    return *this;
}

std::string& ImmutableStructure1::Builder::mutable_s1()
{
    mpObject->mBits |= bitmask_s1();
    return mpObject->mS1;
}

void ImmutableStructure1::Builder::erase_s1()
{
    mpObject->mS1.clear();
    mpObject->mBits &= ~bitmask_s1();
}

int ImmutableStructure2::bitmask_r2()
{
    return 0x1;
}

int ImmutableStructure2::bitmask_o2()
{
    return 0x2;
}

int ImmutableStructure2::bitmask_d2()
{
    return 0x4;
}

int ImmutableStructure2::bitmask_s2()
{
    return 0x8;
}

ImmutableStructure2::Builder::Builder()
        : ImmutableStructure1::Builder(new ImmutableStructure2())
{
}

ImmutableStructure2::Builder::Builder(const ImmutableStructure2& object)
        : ImmutableStructure1::Builder(new ImmutableStructure2())
{
    *(ImmutableStructure2*)mpObject = object;
}

ImmutableStructure2::Builder::Builder(ImmutableStructure2RPtr pObject)
        : ImmutableStructure1::Builder(pObject)
{
}

ImmutableStructure2::Builder::~Builder()
{
    delete (ImmutableStructure2RPtr)mpObject;
    mpObject = NULL;
}

const ImmutableStructure2& ImmutableStructure2::Builder::build() const
{
    BOOST_ASSERT(mpObject->isInitialized());
    return *(ImmutableStructure2RPtr)mpObject;
}

ImmutableStructure2SPtr ImmutableStructure2::Builder::finalize()
{
    BOOST_ASSERT(mpObject->isInitialized());
    ImmutableStructure2RPtr objectRPtr = (ImmutableStructure2RPtr)mpObject;
    mpObject = NULL;
    return ImmutableStructure2SPtr(objectRPtr);
}

ImmutableStructure2::ImmutableStructure2()
        : mBits(0)
        , mD2  (default_d2())
{
}

ImmutableStructure2::~ImmutableStructure2()
{
}

ImmutableStructure2SPtr ImmutableStructure2::downcast(const ImmutableStructure1SPtr& object)
{
    return boost::static_pointer_cast<ImmutableStructure2>(object);
}

bool ImmutableStructure2::isInitialized() const
{
    if (!ImmutableStructure1::isInitialized()) return false;
    if (!valid_r2()) return false;
    if (!valid_s2()) return false;
    return true;
}

ImmutableStructure2::Builder& ImmutableStructure2::Builder::set_r1(long r1)
{
    return (ImmutableStructure2::Builder&)ImmutableStructure1::Builder::set_r1(r1);
}

ImmutableStructure2::Builder& ImmutableStructure2::Builder::set_o1(long o1)
{
    return (ImmutableStructure2::Builder&)ImmutableStructure1::Builder::set_o1(o1);
}

ImmutableStructure2::Builder& ImmutableStructure2::Builder::set_d1(long d1)
{
    return (ImmutableStructure2::Builder&)ImmutableStructure1::Builder::set_d1(d1);
}

ImmutableStructure2::Builder& ImmutableStructure2::Builder::set_s1(const std::string& s1)
{
    return (ImmutableStructure2::Builder&)ImmutableStructure1::Builder::set_s1(s1);
}

long ImmutableStructure2::r2() const
{
    BOOST_ASSERT(valid_r2());
    return mR2;
}

bool ImmutableStructure2::valid_r2() const
{
    return (mBits & bitmask_r2()) != 0;
}

ImmutableStructure2::Builder& ImmutableStructure2::Builder::set_r2(long r2)
{
    ((ImmutableStructure2*)mpObject)->mR2    = r2;
    ((ImmutableStructure2*)mpObject)->mBits |= bitmask_r2();
    return *this;
}

void ImmutableStructure2::Builder::erase_r2()
{
    ((ImmutableStructure2*)mpObject)->mR2    =  0;
    ((ImmutableStructure2*)mpObject)->mBits &= ~bitmask_r2();
}

long ImmutableStructure2::o2() const
{
    BOOST_ASSERT(exist_o2());
    return mO2;
}

bool ImmutableStructure2::exist_o2() const
{
    return (mBits & bitmask_o2()) != 0;
}

ImmutableStructure2::Builder& ImmutableStructure2::Builder::set_o2(long o2)
{
    ((ImmutableStructure2*)mpObject)->mO2    = o2;
    ((ImmutableStructure2*)mpObject)->mBits |= bitmask_o2();
    return *this;
}

void ImmutableStructure2::Builder::clear_o2()
{
    ((ImmutableStructure2*)mpObject)->mO2    =  0;
    ((ImmutableStructure2*)mpObject)->mBits &= ~bitmask_o2();
}

long ImmutableStructure2::d2() const
{
    return mD2;
}

bool ImmutableStructure2::changed_d2() const
{
    return (mBits & bitmask_d2()) != 0;
}

long ImmutableStructure2::default_d2()
{
    return 2;
}

ImmutableStructure2::Builder& ImmutableStructure2::Builder::set_d2(long d2)
{
    ((ImmutableStructure2*)mpObject)->mD2    = d2;
    ((ImmutableStructure2*)mpObject)->mBits |= bitmask_d2();
    return *this;
}

ImmutableStructure2::Builder& ImmutableStructure2::Builder::update_d2(long d2)
{
    if (((ImmutableStructure2*)mpObject)->default_d2() != d2)
        return set_d2(d2);

    reset_d2();
    return *this;
}

void ImmutableStructure2::Builder::reset_d2()
{
    ((ImmutableStructure2*)mpObject)->mD2    =  ((ImmutableStructure2*)mpObject)->default_d2();
    ((ImmutableStructure2*)mpObject)->mBits &= ~bitmask_d2                                  ();
}

const std::string& ImmutableStructure2::s2() const
{
    BOOST_ASSERT(valid_s2());
    return mS2;
}

bool ImmutableStructure2::valid_s2() const
{
    return (mBits & bitmask_s2()) != 0;
}

ImmutableStructure2::Builder& ImmutableStructure2::Builder::set_s2(const std::string& s2)
{
    ((ImmutableStructure2*)mpObject)->mS2    = s2;
    ((ImmutableStructure2*)mpObject)->mBits |= bitmask_s2();
    return *this;
}

std::string& ImmutableStructure2::Builder::mutable_s2()
{
    ((ImmutableStructure2*)mpObject)->mBits |= bitmask_s2();
    return ((ImmutableStructure2*)mpObject)->mS2;
}

void ImmutableStructure2::Builder::erase_s2()
{
    ((ImmutableStructure2*)mpObject)->mS2.clear();
    ((ImmutableStructure2*)mpObject)->mBits &= ~bitmask_s2();
}

int ImmutableStructure3::bitmask_r3()
{
    return 0x1;
}

int ImmutableStructure3::bitmask_o3()
{
    return 0x2;
}

int ImmutableStructure3::bitmask_d3()
{
    return 0x4;
}

int ImmutableStructure3::bitmask_s3()
{
    return 0x8;
}

ImmutableStructure3::Builder::Builder()
        : ImmutableStructure2::Builder(new ImmutableStructure3())
{
}

ImmutableStructure3::Builder::Builder(const ImmutableStructure3& object)
        : ImmutableStructure2::Builder(new ImmutableStructure3())
{
    *(ImmutableStructure3*)mpObject = object;
}

ImmutableStructure3::Builder::Builder(ImmutableStructure3RPtr pObject)
        : ImmutableStructure2::Builder(pObject)
{
}

ImmutableStructure3::Builder::~Builder()
{
    delete (ImmutableStructure3RPtr)mpObject;
    mpObject = NULL;
}

const ImmutableStructure3& ImmutableStructure3::Builder::build() const
{
    BOOST_ASSERT(mpObject->isInitialized());
    return *(ImmutableStructure3RPtr)mpObject;
}

ImmutableStructure3SPtr ImmutableStructure3::Builder::finalize()
{
    BOOST_ASSERT(mpObject->isInitialized());
    ImmutableStructure3RPtr objectRPtr = (ImmutableStructure3RPtr)mpObject;
    mpObject = NULL;
    return ImmutableStructure3SPtr(objectRPtr);
}

ImmutableStructure3::ImmutableStructure3()
        : mBits(0)
        , mD3  (default_d3())
{
}

ImmutableStructure3::~ImmutableStructure3()
{
}

ImmutableStructure3SPtr ImmutableStructure3::downcast(const ImmutableStructure1SPtr& object)
{
    return boost::static_pointer_cast<ImmutableStructure3>(object);
}

bool ImmutableStructure3::isInitialized() const
{
    if (!ImmutableStructure2::isInitialized()) return false;
    if (!valid_r3()) return false;
    if (!valid_s3()) return false;
    return true;
}

ImmutableStructure3::Builder& ImmutableStructure3::Builder::set_r1(long r1)
{
    return (ImmutableStructure3::Builder&)ImmutableStructure1::Builder::set_r1(r1);
}

ImmutableStructure3::Builder& ImmutableStructure3::Builder::set_o1(long o1)
{
    return (ImmutableStructure3::Builder&)ImmutableStructure1::Builder::set_o1(o1);
}

ImmutableStructure3::Builder& ImmutableStructure3::Builder::set_d1(long d1)
{
    return (ImmutableStructure3::Builder&)ImmutableStructure1::Builder::set_d1(d1);
}

ImmutableStructure3::Builder& ImmutableStructure3::Builder::set_s1(const std::string& s1)
{
    return (ImmutableStructure3::Builder&)ImmutableStructure1::Builder::set_s1(s1);
}

ImmutableStructure3::Builder& ImmutableStructure3::Builder::set_r2(long r2)
{
    return (ImmutableStructure3::Builder&)ImmutableStructure2::Builder::set_r2(r2);
}

ImmutableStructure3::Builder& ImmutableStructure3::Builder::set_o2(long o2)
{
    return (ImmutableStructure3::Builder&)ImmutableStructure2::Builder::set_o2(o2);
}

ImmutableStructure3::Builder& ImmutableStructure3::Builder::set_d2(long d2)
{
    return (ImmutableStructure3::Builder&)ImmutableStructure2::Builder::set_d2(d2);
}

ImmutableStructure3::Builder& ImmutableStructure3::Builder::set_s2(const std::string& s2)
{
    return (ImmutableStructure3::Builder&)ImmutableStructure2::Builder::set_s2(s2);
}

long ImmutableStructure3::r3() const
{
    BOOST_ASSERT(valid_r3());
    return mR3;
}

bool ImmutableStructure3::valid_r3() const
{
    return (mBits & bitmask_r3()) != 0;
}

ImmutableStructure3::Builder& ImmutableStructure3::Builder::set_r3(long r3)
{
    ((ImmutableStructure3*)mpObject)->mR3    = r3;
    ((ImmutableStructure3*)mpObject)->mBits |= bitmask_r3();
    return *this;
}

void ImmutableStructure3::Builder::erase_r3()
{
    ((ImmutableStructure3*)mpObject)->mR3    =  0;
    ((ImmutableStructure3*)mpObject)->mBits &= ~bitmask_r3();
}

long ImmutableStructure3::o3() const
{
    BOOST_ASSERT(exist_o3());
    return mO3;
}

bool ImmutableStructure3::exist_o3() const
{
    return (mBits & bitmask_o3()) != 0;
}

ImmutableStructure3::Builder& ImmutableStructure3::Builder::set_o3(long o3)
{
    ((ImmutableStructure3*)mpObject)->mO3    = o3;
    ((ImmutableStructure3*)mpObject)->mBits |= bitmask_o3();
    return *this;
}

void ImmutableStructure3::Builder::clear_o3()
{
    ((ImmutableStructure3*)mpObject)->mO3    =  0;
    ((ImmutableStructure3*)mpObject)->mBits &= ~bitmask_o3();
}

long ImmutableStructure3::d3() const
{
    return mD3;
}

bool ImmutableStructure3::changed_d3() const
{
    return (mBits & bitmask_d3()) != 0;
}

long ImmutableStructure3::default_d3()
{
    return 3;
}

ImmutableStructure3::Builder& ImmutableStructure3::Builder::set_d3(long d3)
{
    ((ImmutableStructure3*)mpObject)->mD3    = d3;
    ((ImmutableStructure3*)mpObject)->mBits |= bitmask_d3();
    return *this;
}

ImmutableStructure3::Builder& ImmutableStructure3::Builder::update_d3(long d3)
{
    if (((ImmutableStructure3*)mpObject)->default_d3() != d3)
        return set_d3(d3);

    reset_d3();
    return *this;
}

void ImmutableStructure3::Builder::reset_d3()
{
    ((ImmutableStructure3*)mpObject)->mD3    =  ((ImmutableStructure3*)mpObject)->default_d3();
    ((ImmutableStructure3*)mpObject)->mBits &= ~bitmask_d3                                  ();
}

const std::string& ImmutableStructure3::s3() const
{
    BOOST_ASSERT(valid_s3());
    return mS3;
}

bool ImmutableStructure3::valid_s3() const
{
    return (mBits & bitmask_s3()) != 0;
}

ImmutableStructure3::Builder& ImmutableStructure3::Builder::set_s3(const std::string& s3)
{
    ((ImmutableStructure3*)mpObject)->mS3    = s3;
    ((ImmutableStructure3*)mpObject)->mBits |= bitmask_s3();
    return *this;
}

std::string& ImmutableStructure3::Builder::mutable_s3()
{
    ((ImmutableStructure3*)mpObject)->mBits |= bitmask_s3();
    return ((ImmutableStructure3*)mpObject)->mS3;
}

void ImmutableStructure3::Builder::erase_s3()
{
    ((ImmutableStructure3*)mpObject)->mS3.clear();
    ((ImmutableStructure3*)mpObject)->mBits &= ~bitmask_s3();
}

int ImmutableStructureAggregate::bitmask_rs()
{
    return 0x1;
}

int ImmutableStructureAggregate::bitmask_os()
{
    return 0x2;
}

int ImmutableStructureAggregate::bitmask_rrs()
{
    return 0x4;
}

int ImmutableStructureAggregate::bitmask_ors()
{
    return 0x8;
}

int ImmutableStructureAggregate::bitmask_rns()
{
    return 0x10;
}

ImmutableStructureAggregate::Builder::Builder()
        : mpObject(new ImmutableStructureAggregate())
{
}

ImmutableStructureAggregate::Builder::Builder(const ImmutableStructureAggregate& object)
        : mpObject(new ImmutableStructureAggregate())
{
    *(ImmutableStructureAggregate*)mpObject = object;
}

ImmutableStructureAggregate::Builder::Builder(ImmutableStructureAggregateRPtr pObject)
        : mpObject(pObject)
{
}

ImmutableStructureAggregate::Builder::~Builder()
{
    delete (ImmutableStructureAggregateRPtr)mpObject;
    mpObject = NULL;
}

const ImmutableStructureAggregate& ImmutableStructureAggregate::Builder::build() const
{
    BOOST_ASSERT(mpObject->isInitialized());
    return *(ImmutableStructureAggregateRPtr)mpObject;
}

ImmutableStructureAggregateSPtr ImmutableStructureAggregate::Builder::finalize()
{
    BOOST_ASSERT(mpObject->isInitialized());
    ImmutableStructureAggregateRPtr objectRPtr = (ImmutableStructureAggregateRPtr)mpObject;
    mpObject = NULL;
    return ImmutableStructureAggregateSPtr(objectRPtr);
}

ImmutableStructureAggregate::ImmutableStructureAggregate()
        : mBits(0)
{
}

ImmutableStructureAggregate::~ImmutableStructureAggregate()
{
}

bool ImmutableStructureAggregate::isInitialized() const
{
    if (!valid_rs()) return false;
    if (!valid_rrs()) return false;
    return true;
}

const ImmutableStructure1& ImmutableStructureAggregate::rs() const
{
    BOOST_ASSERT(valid_rs());
    return mRs;
}

bool ImmutableStructureAggregate::valid_rs() const
{
    return (mBits & bitmask_rs()) != 0;
}

ImmutableStructureAggregate::Builder& ImmutableStructureAggregate::Builder::set_rs(const ImmutableStructure1& rs)
{
    mpObject->mRs    = rs;
    mpObject->mBits |= bitmask_rs();
    return *this;
}

ImmutableStructure1& ImmutableStructureAggregate::Builder::mutable_rs()
{
    mpObject->mBits |= bitmask_rs();
    return mpObject->mRs;
}

void ImmutableStructureAggregate::Builder::erase_rs()
{
    mpObject->mRs    =  ImmutableStructure1();
    mpObject->mBits &= ~bitmask_rs            ();
}

const ImmutableStructure1& ImmutableStructureAggregate::os() const
{
    BOOST_ASSERT(exist_os());
    return mOs;
}

bool ImmutableStructureAggregate::exist_os() const
{
    return (mBits & bitmask_os()) != 0;
}

ImmutableStructureAggregate::Builder& ImmutableStructureAggregate::Builder::set_os(const ImmutableStructure1& os)
{
    mpObject->mOs    = os;
    mpObject->mBits |= bitmask_os();
    return *this;
}

ImmutableStructure1& ImmutableStructureAggregate::Builder::mutable_os()
{
    mpObject->mBits |= bitmask_os();
    return mpObject->mOs;
}

void ImmutableStructureAggregate::Builder::clear_os()
{
    mpObject->mOs    =  ImmutableStructure1();
    mpObject->mBits &= ~bitmask_os            ();
}

const ImmutableStructure1SPtr& ImmutableStructureAggregate::rrs() const
{
    BOOST_ASSERT(valid_rrs());
    return mRrs;
}

bool ImmutableStructureAggregate::valid_rrs() const
{
    return (mBits & bitmask_rrs()) != 0;
}

ImmutableStructureAggregate::Builder& ImmutableStructureAggregate::Builder::set_rrs(const ImmutableStructure1SPtr& rrs)
{
    mpObject->mRrs   = rrs;
    mpObject->mBits |= bitmask_rrs();
    return *this;
}

void ImmutableStructureAggregate::Builder::erase_rrs()
{
    mpObject->mRrs.reset();
    mpObject->mBits &= ~bitmask_rrs();
}

const ImmutableStructure1SPtr& ImmutableStructureAggregate::ors() const
{
    BOOST_ASSERT(exist_ors());
    return mOrs;
}

bool ImmutableStructureAggregate::exist_ors() const
{
    return (mBits & bitmask_ors()) != 0;
}

ImmutableStructureAggregate::Builder& ImmutableStructureAggregate::Builder::set_ors(const ImmutableStructure1SPtr& ors)
{
    mpObject->mOrs   = ors;
    mpObject->mBits |= bitmask_ors();
    return *this;
}

void ImmutableStructureAggregate::Builder::clear_ors()
{
    mpObject->mOrs.reset();
    mpObject->mBits &= ~bitmask_ors();
}

const ImmutableStructure1SPtr& ImmutableStructureAggregate::rns() const
{
    return mRns;
}

bool ImmutableStructureAggregate::changed_rns() const
{
    return (mBits & bitmask_rns()) != 0;
}

ImmutableStructure1SPtr ImmutableStructureAggregate::default_rns()
{
    static ImmutableStructure1SPtr defaultObject;
    return defaultObject;
}

ImmutableStructureAggregate::Builder& ImmutableStructureAggregate::Builder::set_rns(const ImmutableStructure1SPtr& rns)
{
    mpObject->mRns   = rns;
    mpObject->mBits |= bitmask_rns();
    return *this;
}

ImmutableStructureAggregate::Builder& ImmutableStructureAggregate::Builder::update_rns(const ImmutableStructure1SPtr& rns)
{
    if (mpObject->default_rns() != rns)
        return set_rns(rns);

    reset_rns();
    return *this;
}

void ImmutableStructureAggregate::Builder::reset_rns()
{
    mpObject->mRns   =  mpObject->default_rns();
    mpObject->mBits &= ~bitmask_rns          ();
}

