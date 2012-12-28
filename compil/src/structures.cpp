// Boost C++ Utility
#include <boost/assert.hpp>

#include "structures.h"
// Standard C Library
#include <stddef.h>

int StructureIsInitialize::bitmask_r()
{
    return 0x1;
}

int StructureIsInitialize::bitmask_o()
{
    return 0x2;
}

int StructureIsInitialize::bitmask_d()
{
    return 0x4;
}

StructureIsInitialize::StructureIsInitialize()
        : mBits(0)
        , mD   (default_d())
{
}

StructureIsInitialize::~StructureIsInitialize()
{
}

bool StructureIsInitialize::isInitialized() const
{
    if (!valid_r()) return false;
    return true;
}

long StructureIsInitialize::r() const
{
    BOOST_ASSERT(valid_r());
    return mR;
}

bool StructureIsInitialize::valid_r() const
{
    return (mBits & bitmask_r()) != 0;
}

StructureIsInitialize& StructureIsInitialize::set_r(long r)
{
    mR     = r;
    mBits |= bitmask_r();
    return *this;
}

void StructureIsInitialize::erase_r()
{
    mR     =  0;
    mBits &= ~bitmask_r();
}

long StructureIsInitialize::o() const
{
    BOOST_ASSERT(exist_o());
    return mO;
}

bool StructureIsInitialize::exist_o() const
{
    return (mBits & bitmask_o()) != 0;
}

StructureIsInitialize& StructureIsInitialize::set_o(long o)
{
    mO     = o;
    mBits |= bitmask_o();
    return *this;
}

void StructureIsInitialize::clear_o()
{
    mO     =  0;
    mBits &= ~bitmask_o();
}

long StructureIsInitialize::d() const
{
    return mD;
}

bool StructureIsInitialize::changed_d() const
{
    return (mBits & bitmask_d()) != 0;
}

long StructureIsInitialize::default_d()
{
    return 1;
}

StructureIsInitialize& StructureIsInitialize::set_d(long d)
{
    mD     = d;
    mBits |= bitmask_d();
    return *this;
}

StructureIsInitialize& StructureIsInitialize::update_d(long d)
{
    if (default_d() != d)
        return set_d(d);

    reset_d();
    return *this;
}

void StructureIsInitialize::reset_d()
{
    mD     =  default_d();
    mBits &= ~bitmask_d();
}

StructureIsInitialize1::StructureIsInitialize1()
{
    set_r(alter_r());
}

StructureIsInitialize1::~StructureIsInitialize1()
{
}

StructureIsInitialize1SPtr StructureIsInitialize1::downcast(const StructureIsInitializeSPtr& object)
{
    return boost::static_pointer_cast<StructureIsInitialize1>(object);
}

long StructureIsInitialize1::alter_r()
{
    return 5;
}

int StructureIsInitialize2::bitmask_r2()
{
    return 0x1;
}

StructureIsInitialize2::StructureIsInitialize2()
        : mBits(0)
{
}

StructureIsInitialize2::~StructureIsInitialize2()
{
}

StructureIsInitialize2SPtr StructureIsInitialize2::downcast(const StructureIsInitializeSPtr& object)
{
    return boost::static_pointer_cast<StructureIsInitialize2>(object);
}

bool StructureIsInitialize2::isInitialized() const
{
    if (!StructureIsInitialize::isInitialized()) return false;
    if (!valid_r2()) return false;
    return true;
}

long StructureIsInitialize2::r2() const
{
    BOOST_ASSERT(valid_r2());
    return mR2;
}

bool StructureIsInitialize2::valid_r2() const
{
    return (mBits & bitmask_r2()) != 0;
}

StructureIsInitialize2& StructureIsInitialize2::set_r2(long r2)
{
    mR2    = r2;
    mBits |= bitmask_r2();
    return *this;
}

void StructureIsInitialize2::erase_r2()
{
    mR2    =  0;
    mBits &= ~bitmask_r2();
}

StructureNonControlledInherit::StructureNonControlledInherit()
{
}

StructureNonControlledInherit::~StructureNonControlledInherit()
{
}

StructureNonControlledInheritSPtr StructureNonControlledInherit::downcast(const StructureIsInitializeSPtr& object)
{
    return boost::static_pointer_cast<StructureNonControlledInherit>(object);
}

StructureNonControlledInheritSPtr StructureNonControlledInherit::shared_from_this()
{
    return boost::static_pointer_cast<StructureNonControlledInherit>(
        boost::enable_shared_from_this<StructureIsInitialize>::shared_from_this());
}

StructureNonControlledInheritSCPtr StructureNonControlledInherit::shared_from_this() const
{
    return boost::static_pointer_cast<const StructureNonControlledInherit>(
        boost::enable_shared_from_this<StructureIsInitialize>::shared_from_this());
}

int StructureIsInitialize3::bitmask_r3()
{
    return 0x1;
}

StructureIsInitialize3::StructureIsInitialize3()
        : mBits(0)
{
}

StructureIsInitialize3::~StructureIsInitialize3()
{
}

StructureIsInitialize3SPtr StructureIsInitialize3::downcast(const StructureIsInitializeSPtr& object)
{
    return boost::static_pointer_cast<StructureIsInitialize3>(object);
}

StructureIsInitialize3SPtr StructureIsInitialize3::shared_from_this()
{
    return boost::static_pointer_cast<StructureIsInitialize3>(
        boost::enable_shared_from_this<StructureIsInitialize>::shared_from_this());
}

StructureIsInitialize3SCPtr StructureIsInitialize3::shared_from_this() const
{
    return boost::static_pointer_cast<const StructureIsInitialize3>(
        boost::enable_shared_from_this<StructureIsInitialize>::shared_from_this());
}

bool StructureIsInitialize3::isInitialized() const
{
    // structure StructureNonControlledInherit is not controlled. This function assume it is initilized
    if (!StructureIsInitialize::isInitialized()) return false;
    if (!valid_r3()) return false;
    return true;
}

long StructureIsInitialize3::r3() const
{
    BOOST_ASSERT(valid_r3());
    return mR3;
}

bool StructureIsInitialize3::valid_r3() const
{
    return (mBits & bitmask_r3()) != 0;
}

StructureIsInitialize3& StructureIsInitialize3::set_r3(long r3)
{
    mR3    = r3;
    mBits |= bitmask_r3();
    return *this;
}

void StructureIsInitialize3::erase_r3()
{
    mR3    =  0;
    mBits &= ~bitmask_r3();
}

StructureNonControlled::StructureNonControlled()
{
}

StructureNonControlled::~StructureNonControlled()
{
}

StructureNonControlledSPtr StructureNonControlled::downcast(const StructureIsInitializeSPtr& object)
{
    return boost::static_pointer_cast<StructureNonControlled>(object);
}

int StructureIsInitialize4::bitmask_r4()
{
    return 0x1;
}

StructureIsInitialize4::StructureIsInitialize4()
        : mBits(0)
{
}

StructureIsInitialize4::~StructureIsInitialize4()
{
}

StructureIsInitialize4SPtr StructureIsInitialize4::downcast(const StructureIsInitializeSPtr& object)
{
    return boost::static_pointer_cast<StructureIsInitialize4>(object);
}

bool StructureIsInitialize4::isInitialized() const
{
    // structure StructureNonControlled is not controlled. This function assume it is initilized
    if (!StructureIsInitialize::isInitialized()) return false;
    if (!valid_r4()) return false;
    return true;
}

long StructureIsInitialize4::r4() const
{
    BOOST_ASSERT(valid_r4());
    return mR4;
}

bool StructureIsInitialize4::valid_r4() const
{
    return (mBits & bitmask_r4()) != 0;
}

StructureIsInitialize4& StructureIsInitialize4::set_r4(long r4)
{
    mR4    = r4;
    mBits |= bitmask_r4();
    return *this;
}

void StructureIsInitialize4::erase_r4()
{
    mR4    =  0;
    mBits &= ~bitmask_r4();
}

int StructureIsInitializeVirtual::bitmask_r()
{
    return 0x1;
}

StructureIsInitializeVirtual::StructureIsInitializeVirtual()
        : mBits(0)
{
}

StructureIsInitializeVirtual::~StructureIsInitializeVirtual()
{
}

bool StructureIsInitializeVirtual::isInitialized() const
{
    if (!valid_r()) return false;
    return true;
}

long StructureIsInitializeVirtual::r() const
{
    BOOST_ASSERT(valid_r());
    return mR;
}

bool StructureIsInitializeVirtual::valid_r() const
{
    return (mBits & bitmask_r()) != 0;
}

StructureIsInitializeVirtual& StructureIsInitializeVirtual::set_r(long r)
{
    mR     = r;
    mBits |= bitmask_r();
    return *this;
}

void StructureIsInitializeVirtual::erase_r()
{
    mR     =  0;
    mBits &= ~bitmask_r();
}

StructureNonControlledVirtualInherit::StructureNonControlledVirtualInherit()
{
}

StructureNonControlledVirtualInherit::~StructureNonControlledVirtualInherit()
{
}

StructureNonControlledVirtualInheritSPtr StructureNonControlledVirtualInherit::downcast(const StructureIsInitializeVirtualSPtr& object)
{
    return boost::static_pointer_cast<StructureNonControlledVirtualInherit>(object);
}

int StructureIsInitialize5::bitmask_r5()
{
    return 0x1;
}

StructureIsInitialize5::StructureIsInitialize5()
        : mBits(0)
{
}

StructureIsInitialize5::~StructureIsInitialize5()
{
}

StructureIsInitialize5SPtr StructureIsInitialize5::downcast(const StructureIsInitializeVirtualSPtr& object)
{
    return boost::static_pointer_cast<StructureIsInitialize5>(object);
}

bool StructureIsInitialize5::isInitialized() const
{
    // structure StructureNonControlledVirtualInherit is not controlled. This function assume it is initilized
    if (!StructureIsInitializeVirtual::isInitialized()) return false;
    if (!valid_r5()) return false;
    return true;
}

long StructureIsInitialize5::r5() const
{
    BOOST_ASSERT(valid_r5());
    return mR5;
}

bool StructureIsInitialize5::valid_r5() const
{
    return (mBits & bitmask_r5()) != 0;
}

StructureIsInitialize5& StructureIsInitialize5::set_r5(long r5)
{
    mR5    = r5;
    mBits |= bitmask_r5();
    return *this;
}

void StructureIsInitialize5::erase_r5()
{
    mR5    =  0;
    mBits &= ~bitmask_r5();
}

StructureNonControlledVirtual::StructureNonControlledVirtual()
{
}

StructureNonControlledVirtual::~StructureNonControlledVirtual()
{
}

long StructureNonControlledVirtual::r() const
{
    return mR;
}

StructureNonControlledVirtual& StructureNonControlledVirtual::set_r(long r)
{
    mR = r;
    return *this;
}

int StructureIsInitialize6::bitmask_r6()
{
    return 0x1;
}

StructureIsInitialize6::StructureIsInitialize6()
        : mBits(0)
{
}

StructureIsInitialize6::~StructureIsInitialize6()
{
}

StructureIsInitialize6SPtr StructureIsInitialize6::downcast(const StructureNonControlledVirtualSPtr& object)
{
    return boost::static_pointer_cast<StructureIsInitialize6>(object);
}

bool StructureIsInitialize6::isInitialized() const
{
    // structure StructureNonControlledVirtual is not controlled. This function assume it is initilized
    if (!valid_r6()) return false;
    return true;
}

long StructureIsInitialize6::r6() const
{
    BOOST_ASSERT(valid_r6());
    return mR6;
}

bool StructureIsInitialize6::valid_r6() const
{
    return (mBits & bitmask_r6()) != 0;
}

StructureIsInitialize6& StructureIsInitialize6::set_r6(long r6)
{
    mR6    = r6;
    mBits |= bitmask_r6();
    return *this;
}

void StructureIsInitialize6::erase_r6()
{
    mR6    =  0;
    mBits &= ~bitmask_r6();
}

int StructureIsVoid::bitmask_o()
{
    return 0x1;
}

StructureIsVoid::StructureIsVoid()
        : mBits(0)
{
}

StructureIsVoid::~StructureIsVoid()
{
}

bool StructureIsVoid::isInitialized() const
{
    return true;
}

bool StructureIsVoid::isVoid() const
{
    if (exist_o()) return false;
    return true;
}

long StructureIsVoid::o() const
{
    BOOST_ASSERT(exist_o());
    return mO;
}

bool StructureIsVoid::exist_o() const
{
    return (mBits & bitmask_o()) != 0;
}

StructureIsVoid& StructureIsVoid::set_o(long o)
{
    mO     = o;
    mBits |= bitmask_o();
    return *this;
}

void StructureIsVoid::clear_o()
{
    mO     =  0;
    mBits &= ~bitmask_o();
}

int StructureIsVoid1::bitmask_o1()
{
    return 0x1;
}

StructureIsVoid1::StructureIsVoid1()
        : mBits(0)
{
}

StructureIsVoid1::~StructureIsVoid1()
{
}

StructureIsVoid1SPtr StructureIsVoid1::downcast(const StructureIsVoidSPtr& object)
{
    return boost::static_pointer_cast<StructureIsVoid1>(object);
}

bool StructureIsVoid1::isInitialized() const
{
    if (!StructureIsVoid::isInitialized()) return false;
    return true;
}

bool StructureIsVoid1::isVoid() const
{
    if (!StructureIsVoid::isVoid()) return false;
    if (exist_o1()) return false;
    return true;
}

long StructureIsVoid1::o1() const
{
    BOOST_ASSERT(exist_o1());
    return mO1;
}

bool StructureIsVoid1::exist_o1() const
{
    return (mBits & bitmask_o1()) != 0;
}

StructureIsVoid1& StructureIsVoid1::set_o1(long o1)
{
    mO1    = o1;
    mBits |= bitmask_o1();
    return *this;
}

void StructureIsVoid1::clear_o1()
{
    mO1    =  0;
    mBits &= ~bitmask_o1();
}

EStructureIsInitializeVirtualId::EStructureIsInitializeVirtualId()
        : mValue(kInvalid)
{
}

EStructureIsInitializeVirtualId::EStructureIsInitializeVirtualId(long value)
        : mValue(value)
{
}

const EStructureIsInitializeVirtualId EStructureIsInitializeVirtualId::invalid()
{
    return EStructureIsInitializeVirtualId(kInvalid);
}

const EStructureIsInitializeVirtualId EStructureIsInitializeVirtualId::structureIsInitializeVirtual()
{
    return EStructureIsInitializeVirtualId(kStructureIsInitializeVirtual);
}

long EStructureIsInitializeVirtualId::value() const
{
    return mValue;
}

const char* EStructureIsInitializeVirtualId::shortName(long value)
{
    static const char* names[] =
    {
        "", // alignment
        "StructureIsInitializeVirtual",
    };
    return names[(size_t)value];
}

const char* EStructureIsInitializeVirtualId::shortName() const
{
    return shortName(value());
}

bool EStructureIsInitializeVirtualId::operator==(const EStructureIsInitializeVirtualId& rValue) const
{
    return mValue == rValue.mValue;
}

bool EStructureIsInitializeVirtualId::operator!=(const EStructureIsInitializeVirtualId& rValue) const
{
    return mValue != rValue.mValue;
}

EStructureIsInitializeVirtualId StructureIsInitializeVirtual::staticStructureIsInitializeVirtualId()
{
    return EStructureIsInitializeVirtualId::structureIsInitializeVirtual();
}

EStructureIsInitializeVirtualId StructureIsInitializeVirtual::runtimeStructureIsInitializeVirtualId() const
{
    return staticStructureIsInitializeVirtualId();
}

StructureIsInitializeVirtualSPtr StructureIsInitializeVirtualFactory::clone(const StructureIsInitializeVirtualSPtr& pObject)
{
    switch (pObject->runtimeStructureIsInitializeVirtualId().value())
    {
        case EStructureIsInitializeVirtualId::kStructureIsInitializeVirtual:
        {
            StructureIsInitializeVirtualSPtr pClone(new StructureIsInitializeVirtual());
            *pClone = *pObject;
            return pClone;
        }
        default:
            BOOST_ASSERT(false && "unknown objId");
    }
    return StructureIsInitializeVirtualSPtr();
}

EStructureNonControlledVirtualId::EStructureNonControlledVirtualId()
        : mValue(kInvalid)
{
}

EStructureNonControlledVirtualId::EStructureNonControlledVirtualId(long value)
        : mValue(value)
{
}

const EStructureNonControlledVirtualId EStructureNonControlledVirtualId::invalid()
{
    return EStructureNonControlledVirtualId(kInvalid);
}

const EStructureNonControlledVirtualId EStructureNonControlledVirtualId::structureNonControlledVirtual()
{
    return EStructureNonControlledVirtualId(kStructureNonControlledVirtual);
}

long EStructureNonControlledVirtualId::value() const
{
    return mValue;
}

const char* EStructureNonControlledVirtualId::shortName(long value)
{
    static const char* names[] =
    {
        "", // alignment
        "StructureNonControlledVirtual",
    };
    return names[(size_t)value];
}

const char* EStructureNonControlledVirtualId::shortName() const
{
    return shortName(value());
}

bool EStructureNonControlledVirtualId::operator==(const EStructureNonControlledVirtualId& rValue) const
{
    return mValue == rValue.mValue;
}

bool EStructureNonControlledVirtualId::operator!=(const EStructureNonControlledVirtualId& rValue) const
{
    return mValue != rValue.mValue;
}

EStructureNonControlledVirtualId StructureNonControlledVirtual::staticStructureNonControlledVirtualId()
{
    return EStructureNonControlledVirtualId::structureNonControlledVirtual();
}

EStructureNonControlledVirtualId StructureNonControlledVirtual::runtimeStructureNonControlledVirtualId() const
{
    return staticStructureNonControlledVirtualId();
}

StructureNonControlledVirtualSPtr StructureNonControlledVirtualFactory::clone(const StructureNonControlledVirtualSPtr& pObject)
{
    switch (pObject->runtimeStructureNonControlledVirtualId().value())
    {
        case EStructureNonControlledVirtualId::kStructureNonControlledVirtual:
        {
            StructureNonControlledVirtualSPtr pClone(new StructureNonControlledVirtual());
            *pClone = *pObject;
            return pClone;
        }
        default:
            BOOST_ASSERT(false && "unknown objId");
    }
    return StructureNonControlledVirtualSPtr();
}

StructureBase::Builder::Builder()
        : mpObject(new StructureBase())
{
}

StructureBase::Builder::Builder(const StructureBase& object)
        : mpObject(new StructureBase())
{
    *(StructureBase*)mpObject = object;
}

StructureBase::Builder::Builder(StructureBaseRPtr pObject)
        : mpObject(pObject)
{
}

StructureBase::Builder::~Builder()
{
    delete (StructureBaseRPtr)mpObject;
    mpObject = NULL;
}

const StructureBase& StructureBase::Builder::build() const
{
    return *(StructureBaseRPtr)mpObject;
}

StructureBaseSPtr StructureBase::Builder::finalize()
{
    StructureBaseRPtr objectRPtr = (StructureBaseRPtr)mpObject;
    mpObject = NULL;
    return StructureBaseSPtr(objectRPtr);
}

StructureBase::StructureBase()
{
}

StructureBase::~StructureBase()
{
}

StructureAbstract::StructureAbstract()
{
}

StructureAbstract::~StructureAbstract()
{
}

StructureAbstractSPtr StructureAbstract::downcast(const StructureBaseSPtr& object)
{
    return boost::static_pointer_cast<StructureAbstract>(object);
}

StructureLeaf::Builder::Builder()
        : StructureAbstract::Builder(new StructureLeaf())
{
}

StructureLeaf::Builder::Builder(const StructureLeaf& object)
        : StructureAbstract::Builder(new StructureLeaf())
{
    *(StructureLeaf*)mpObject = object;
}

StructureLeaf::Builder::Builder(StructureLeafRPtr pObject)
        : StructureAbstract::Builder(pObject)
{
}

StructureLeaf::Builder::~Builder()
{
    delete (StructureLeafRPtr)mpObject;
    mpObject = NULL;
}

const StructureLeaf& StructureLeaf::Builder::build() const
{
    return *(StructureLeafRPtr)mpObject;
}

StructureLeafSPtr StructureLeaf::Builder::finalize()
{
    StructureLeafRPtr objectRPtr = (StructureLeafRPtr)mpObject;
    mpObject = NULL;
    return StructureLeafSPtr(objectRPtr);
}

StructureLeaf::StructureLeaf()
{
}

StructureLeaf::~StructureLeaf()
{
}

StructureLeafSPtr StructureLeaf::downcast(const StructureBaseSPtr& object)
{
    return boost::static_pointer_cast<StructureLeaf>(object);
}

