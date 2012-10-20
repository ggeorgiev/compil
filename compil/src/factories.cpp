// Boost C++ Utility
#include <boost/assert.hpp>

#include "factories.h"
// Standard C Library
#include <stddef.h>

namespace factories
{

ObjBase::ObjBase()
{
}

ObjBase::~ObjBase()
{
}

ObjBase::EInnerBase::EInnerBase()
        : mValue(kInvalid)
{
}

ObjBase::EInnerBase::EInnerBase(long value)
        : mValue(value)
{
}

const ObjBase::EInnerBase ObjBase::EInnerBase::invalid()
{
    return EInnerBase(kInvalid);
}

long ObjBase::EInnerBase::value() const
{
    return mValue;
}

const char* ObjBase::EInnerBase::shortName(long value)
{
    static const char* names[] = 
    {
        "", // alignment
    };
    return names[(size_t)value];
}

const char* ObjBase::EInnerBase::shortName() const
{
    return shortName(value());
}

bool ObjBase::EInnerBase::operator==(const EInnerBase& rValue) const
{
    return mValue == rValue.mValue;
}

bool ObjBase::EInnerBase::operator!=(const EInnerBase& rValue) const
{
    return mValue != rValue.mValue;
}

size_t ObjBase::staticInprocId()
{
    return (size_t)"factories.ObjBase";
}

size_t ObjBase::runtimeInprocId() const
{
    return staticInprocId();
}

const ObjBase::EInnerBase& ObjBase::innerBase() const
{
    return mInnerBase;
}

ObjBase& ObjBase::set_innerBase(const EInnerBase& innerBase)
{
    mInnerBase = innerBase;
    return *this;
}

ObjBase::EInnerBase& ObjBase::mutable_innerBase()
{
    return mInnerBase;
}

IObjBase::Builder::Builder()
        : mpObject(new IObjBase())
{
}

IObjBase::Builder::Builder(const IObjBase& object)
        : mpObject(new IObjBase())
{
    *(IObjBase*)mpObject = object;
}

IObjBase::Builder::Builder(IObjBaseRPtr pObject)
        : mpObject(pObject)
{
}

IObjBase::Builder::~Builder()
{
    delete (IObjBaseRPtr)mpObject;
    mpObject = NULL;
}

const IObjBase& IObjBase::Builder::build() const
{
    return *(IObjBaseRPtr)mpObject;
}

IObjBaseSPtr IObjBase::Builder::finalize()
{
    IObjBaseRPtr objectRPtr = (IObjBaseRPtr)mpObject;
    mpObject = NULL;
    return IObjBaseSPtr(objectRPtr);
}

IObjBase::IObjBase()
{
}

IObjBase::~IObjBase()
{
}

IObjBase::EInnerBase::EInnerBase()
        : mValue(kInvalid)
{
}

IObjBase::EInnerBase::EInnerBase(long value)
        : mValue(value)
{
}

const IObjBase::EInnerBase IObjBase::EInnerBase::invalid()
{
    return EInnerBase(kInvalid);
}

long IObjBase::EInnerBase::value() const
{
    return mValue;
}

const char* IObjBase::EInnerBase::shortName(long value)
{
    static const char* names[] = 
    {
        "", // alignment
    };
    return names[(size_t)value];
}

const char* IObjBase::EInnerBase::shortName() const
{
    return shortName(value());
}

bool IObjBase::EInnerBase::operator==(const EInnerBase& rValue) const
{
    return mValue == rValue.mValue;
}

bool IObjBase::EInnerBase::operator!=(const EInnerBase& rValue) const
{
    return mValue != rValue.mValue;
}

size_t IObjBase::staticInprocId()
{
    return (size_t)"factories.IObjBase";
}

size_t IObjBase::runtimeInprocId() const
{
    return staticInprocId();
}

const IObjBase::EInnerBase& IObjBase::innerBase() const
{
    return mInnerBase;
}

IObjBase::Builder& IObjBase::Builder::set_innerBase(const EInnerBase& innerBase)
{
    mpObject->mInnerBase = innerBase;
    return *this;
}

IObjBase::EInnerBase& IObjBase::Builder::mutable_innerBase()
{
    return mpObject->mInnerBase;
}

Obj::Obj()
{
}

Obj::~Obj()
{
}

Obj::EInner::EInner()
        : mValue(kInvalid)
{
}

Obj::EInner::EInner(long value)
        : mValue(value)
{
}

const Obj::EInner Obj::EInner::invalid()
{
    return EInner(kInvalid);
}

long Obj::EInner::value() const
{
    return mValue;
}

const char* Obj::EInner::shortName(long value)
{
    static const char* names[] = 
    {
        "", // alignment
    };
    return names[(size_t)value];
}

const char* Obj::EInner::shortName() const
{
    return shortName(value());
}

bool Obj::EInner::operator==(const EInner& rValue) const
{
    return mValue == rValue.mValue;
}

bool Obj::EInner::operator!=(const EInner& rValue) const
{
    return mValue != rValue.mValue;
}

ObjRPtr Obj::clone(const Obj& object)
{
    return new Obj((const Obj&)object);
}

bool g_init_Obj =
    PluginObjFactory::registerCloneFunction(Obj::staticInprocId(), &Obj::clone);

size_t Obj::staticInprocId()
{
    return (size_t)"factories.Obj";
}

size_t Obj::runtimeInprocId() const
{
    return staticInprocId();
}

long Obj::o() const
{
    return mO;
}

Obj& Obj::set_o(long o)
{
    mO = o;
    return *this;
}

const Obj::EInner& Obj::inner() const
{
    return mInner;
}

Obj& Obj::set_inner(const EInner& inner)
{
    mInner = inner;
    return *this;
}

Obj::EInner& Obj::mutable_inner()
{
    return mInner;
}

PluginObjFactory::PluginObjFactory()
{
}

PluginObjFactory::~PluginObjFactory()
{
}

bool PluginObjFactory::registerCloneFunction(size_t object, fnClone function)
{
    get().cloneFunctions[object] = function;
    return true;
}

bool PluginObjFactory::registerRelationship(size_t parent, size_t child)
{
    get().relationships.insert(Pair(parent, child));
    return true;
}

bool PluginObjFactory::isParent(size_t parent, size_t child)
{
    return get().relationships.find(Pair(parent, child)) != get().relationships.end();
}

PluginObjFactory& PluginObjFactory::get()
{
    static PluginObjFactory factory;
    return factory;
}

ObjA::ObjA()
{
}

ObjA::~ObjA()
{
}

ObjASPtr ObjA::downcast(const ObjSPtr& object)
{
    return boost::static_pointer_cast<ObjA>(object);
}

ObjRPtr ObjA::clone(const Obj& object)
{
    return new ObjA((const ObjA&)object);
}

bool g_init_ObjA =
       PluginObjFactory::registerCloneFunction(ObjA::staticInprocId(), &ObjA::clone)
    && PluginObjFactory::registerRelationship (Obj::staticInprocId(),  ObjA::staticInprocId());

size_t ObjA::staticInprocId()
{
    return (size_t)"factories.ObjA";
}

size_t ObjA::runtimeInprocId() const
{
    return staticInprocId();
}

long ObjA::a() const
{
    return mA;
}

ObjA& ObjA::set_a(long a)
{
    mA = a;
    return *this;
}

ObjA1::ObjA1()
{
}

ObjA1::~ObjA1()
{
}

ObjA1SPtr ObjA1::downcast(const ObjSPtr& object)
{
    return boost::static_pointer_cast<ObjA1>(object);
}

ObjRPtr ObjA1::clone(const Obj& object)
{
    return new ObjA1((const ObjA1&)object);
}

bool g_init_ObjA1 =
       PluginObjFactory::registerCloneFunction(ObjA1::staticInprocId(), &ObjA1::clone)
    && PluginObjFactory::registerRelationship (ObjA::staticInprocId(),  ObjA1::staticInprocId())
    && PluginObjFactory::registerRelationship (Obj::staticInprocId(),   ObjA1::staticInprocId());

size_t ObjA1::staticInprocId()
{
    return (size_t)"factories.ObjA1";
}

size_t ObjA1::runtimeInprocId() const
{
    return staticInprocId();
}

long ObjA1::a1() const
{
    return mA1;
}

ObjA1& ObjA1::set_a1(long a1)
{
    mA1 = a1;
    return *this;
}

ObjA2::ObjA2()
{
}

ObjA2::~ObjA2()
{
}

ObjA2SPtr ObjA2::downcast(const ObjSPtr& object)
{
    return boost::static_pointer_cast<ObjA2>(object);
}

bool g_init_ObjA2 =
       PluginObjFactory::registerRelationship(ObjA::staticInprocId(), ObjA2::staticInprocId())
    && PluginObjFactory::registerRelationship(Obj::staticInprocId(),  ObjA2::staticInprocId());

size_t ObjA2::staticInprocId()
{
    return (size_t)"factories.ObjA2";
}

size_t ObjA2::runtimeInprocId() const
{
    return staticInprocId();
}

long ObjA2::a2() const
{
    return mA2;
}

ObjA2& ObjA2::set_a2(long a2)
{
    mA2 = a2;
    return *this;
}

ObjB::ObjB()
{
}

ObjB::~ObjB()
{
}

ObjBSPtr ObjB::downcast(const ObjSPtr& object)
{
    return boost::static_pointer_cast<ObjB>(object);
}

long ObjB::b() const
{
    return mB;
}

ObjB& ObjB::set_b(long b)
{
    mB = b;
    return *this;
}

ObjB1::ObjB1()
{
}

ObjB1::~ObjB1()
{
}

ObjB1SPtr ObjB1::downcast(const ObjSPtr& object)
{
    return boost::static_pointer_cast<ObjB1>(object);
}

long ObjB1::b1() const
{
    return mB1;
}

ObjB1& ObjB1::set_b1(long b1)
{
    mB1 = b1;
    return *this;
}

EObjId::EObjId()
        : mValue(kInvalid)
{
}

EObjId::EObjId(long value)
        : mValue(value)
{
}

const EObjId EObjId::invalid()
{
    return EObjId(kInvalid);
}

const EObjId EObjId::obj()
{
    return EObjId(kObj);
}

const EObjId EObjId::objA()
{
    return EObjId(kObjA);
}

const EObjId EObjId::objA2()
{
    return EObjId(kObjA2);
}

const EObjId EObjId::objB1()
{
    return EObjId(kObjB1);
}

long EObjId::value() const
{
    return mValue;
}

const char* EObjId::shortName(long value)
{
    static const char* names[] = 
    {
        "", // alignment
        "Obj",
        "ObjA",
        "ObjA2",
        "ObjB1",
    };
    return names[(size_t)value];
}

const char* EObjId::shortName() const
{
    return shortName(value());
}

bool EObjId::operator==(const EObjId& rValue) const
{
    return mValue == rValue.mValue;
}

bool EObjId::operator!=(const EObjId& rValue) const
{
    return mValue != rValue.mValue;
}

EObjId Obj::staticObjId()
{
    return EObjId::obj();
}

EObjId Obj::runtimeObjId() const
{
    return staticObjId();
}

EObjId ObjA::staticObjId()
{
    return EObjId::objA();
}

EObjId ObjA::runtimeObjId() const
{
    return staticObjId();
}

EObjId ObjA2::staticObjId()
{
    return EObjId::objA2();
}

EObjId ObjA2::runtimeObjId() const
{
    return staticObjId();
}

EObjId ObjB1::staticObjId()
{
    return EObjId::objB1();
}

EObjId ObjB1::runtimeObjId() const
{
    return staticObjId();
}

ObjSPtr HierarchyObjFactory::clone(const ObjSPtr& pObject)
{
    switch (pObject->runtimeObjId().value())
    {
        case EObjId::kObj:
        {
            ObjSPtr pClone(new Obj());
            *pClone = *pObject;
            return pClone;
        }
        case EObjId::kObjA:
        {
            ObjASPtr pClone(new ObjA());
            *pClone = *downcastObjA(pObject);
            return pClone;
        }
        case EObjId::kObjB1:
        {
            ObjB1SPtr pClone(new ObjB1());
            *pClone = *downcastObjB1(pObject);
            return pClone;
        }
        default:
            BOOST_ASSERT(false && "unknown objId");
    }
    return ObjSPtr();
}

ObjASPtr HierarchyObjFactory::downcastObjA(const ObjSPtr& pObject)
{
    bool b = (pObject->runtimeObjId() == ObjA::staticObjId())
          // or any of the derived classes
          || (pObject->runtimeObjId() == ObjA2::staticObjId());

    if (b)
        return boost::static_pointer_cast<ObjA>(pObject);
    return ObjASPtr();
}

ObjA2SPtr HierarchyObjFactory::downcastObjA2(const ObjSPtr& pObject)
{
    bool b = (pObject->runtimeObjId() == ObjA2::staticObjId());

    if (b)
        return boost::static_pointer_cast<ObjA2>(pObject);
    return ObjA2SPtr();
}

ObjB1SPtr HierarchyObjFactory::downcastObjB1(const ObjSPtr& pObject)
{
    bool b = (pObject->runtimeObjId() == ObjB1::staticObjId());

    if (b)
        return boost::static_pointer_cast<ObjB1>(pObject);
    return ObjB1SPtr();
}

IObj::Builder::Builder()
        : mpObject(new IObj())
{
}

IObj::Builder::Builder(const IObj& object)
        : mpObject(IPluginObjFactory::clone<IObj>(object))
{
}

IObj::Builder::Builder(IObjRPtr pObject)
        : mpObject(pObject)
{
}

IObj::Builder::~Builder()
{
    delete (IObjRPtr)mpObject;
    mpObject = NULL;
}

const IObj& IObj::Builder::build() const
{
    return *(IObjRPtr)mpObject;
}

IObjSPtr IObj::Builder::finalize()
{
    IObjRPtr objectRPtr = (IObjRPtr)mpObject;
    mpObject = NULL;
    return IObjSPtr(objectRPtr);
}

IObj::IObj()
{
}

IObj::~IObj()
{
}

IObj::EInner::EInner()
        : mValue(kInvalid)
{
}

IObj::EInner::EInner(long value)
        : mValue(value)
{
}

const IObj::EInner IObj::EInner::invalid()
{
    return EInner(kInvalid);
}

long IObj::EInner::value() const
{
    return mValue;
}

const char* IObj::EInner::shortName(long value)
{
    static const char* names[] = 
    {
        "", // alignment
    };
    return names[(size_t)value];
}

const char* IObj::EInner::shortName() const
{
    return shortName(value());
}

bool IObj::EInner::operator==(const EInner& rValue) const
{
    return mValue == rValue.mValue;
}

bool IObj::EInner::operator!=(const EInner& rValue) const
{
    return mValue != rValue.mValue;
}

IObjRPtr IObj::clone(const IObj& object)
{
    return new IObj((const IObj&)object);
}

bool g_init_IObj =
    IPluginObjFactory::registerCloneFunction(IObj::staticInprocId(), &IObj::clone);

size_t IObj::staticInprocId()
{
    return (size_t)"factories.IObj";
}

size_t IObj::runtimeInprocId() const
{
    return staticInprocId();
}

long IObj::o() const
{
    return mO;
}

IObj::Builder& IObj::Builder::set_o(long o)
{
    mpObject->mO = o;
    return *this;
}

const IObj::EInner& IObj::inner() const
{
    return mInner;
}

IObj::Builder& IObj::Builder::set_inner(const EInner& inner)
{
    mpObject->mInner = inner;
    return *this;
}

IObj::EInner& IObj::Builder::mutable_inner()
{
    return mpObject->mInner;
}

IPluginObjFactory::IPluginObjFactory()
{
}

IPluginObjFactory::~IPluginObjFactory()
{
}

bool IPluginObjFactory::registerCloneFunction(size_t object, fnClone function)
{
    get().cloneFunctions[object] = function;
    return true;
}

bool IPluginObjFactory::registerRelationship(size_t parent, size_t child)
{
    get().relationships.insert(Pair(parent, child));
    return true;
}

bool IPluginObjFactory::isParent(size_t parent, size_t child)
{
    return get().relationships.find(Pair(parent, child)) != get().relationships.end();
}

IPluginObjFactory& IPluginObjFactory::get()
{
    static IPluginObjFactory factory;
    return factory;
}

IObjA::Builder::Builder()
        : IObj::Builder(new IObjA())
{
}

IObjA::Builder::Builder(const IObjA& object)
        : IObj::Builder(IPluginObjFactory::clone<IObjA>(object))
{
}

IObjA::Builder::Builder(IObjARPtr pObject)
        : IObj::Builder(pObject)
{
}

IObjA::Builder::~Builder()
{
    delete (IObjARPtr)mpObject;
    mpObject = NULL;
}

const IObjA& IObjA::Builder::build() const
{
    return *(IObjARPtr)mpObject;
}

IObjASPtr IObjA::Builder::finalize()
{
    IObjARPtr objectRPtr = (IObjARPtr)mpObject;
    mpObject = NULL;
    return IObjASPtr(objectRPtr);
}

IObjA::IObjA()
{
}

IObjA::~IObjA()
{
}

IObjASPtr IObjA::downcast(const IObjSPtr& object)
{
    return boost::static_pointer_cast<IObjA>(object);
}

IObjA::Builder& IObjA::Builder::set_o(long o)
{
    return (IObjA::Builder&)IObj::Builder::set_o(o);
}

IObjA::Builder& IObjA::Builder::set_inner(const EInner& inner)
{
    return (IObjA::Builder&)IObj::Builder::set_inner(inner);
}

IObjRPtr IObjA::clone(const IObj& object)
{
    return new IObjA((const IObjA&)object);
}

bool g_init_IObjA =
       IPluginObjFactory::registerCloneFunction(IObjA::staticInprocId(), &IObjA::clone)
    && IPluginObjFactory::registerRelationship (IObj::staticInprocId(),  IObjA::staticInprocId());

size_t IObjA::staticInprocId()
{
    return (size_t)"factories.IObjA";
}

size_t IObjA::runtimeInprocId() const
{
    return staticInprocId();
}

long IObjA::a() const
{
    return mA;
}

IObjA::Builder& IObjA::Builder::set_a(long a)
{
    ((IObjA*)mpObject)->mA = a;
    return *this;
}

IObjA1::Builder::Builder()
        : IObjA::Builder(new IObjA1())
{
}

IObjA1::Builder::Builder(const IObjA1& object)
        : IObjA::Builder(IPluginObjFactory::clone<IObjA1>(object))
{
}

IObjA1::Builder::Builder(IObjA1RPtr pObject)
        : IObjA::Builder(pObject)
{
}

IObjA1::Builder::~Builder()
{
    delete (IObjA1RPtr)mpObject;
    mpObject = NULL;
}

const IObjA1& IObjA1::Builder::build() const
{
    return *(IObjA1RPtr)mpObject;
}

IObjA1SPtr IObjA1::Builder::finalize()
{
    IObjA1RPtr objectRPtr = (IObjA1RPtr)mpObject;
    mpObject = NULL;
    return IObjA1SPtr(objectRPtr);
}

IObjA1::IObjA1()
{
}

IObjA1::~IObjA1()
{
}

IObjA1SPtr IObjA1::downcast(const IObjSPtr& object)
{
    return boost::static_pointer_cast<IObjA1>(object);
}

IObjA1::Builder& IObjA1::Builder::set_o(long o)
{
    return (IObjA1::Builder&)IObj::Builder::set_o(o);
}

IObjA1::Builder& IObjA1::Builder::set_inner(const EInner& inner)
{
    return (IObjA1::Builder&)IObj::Builder::set_inner(inner);
}

IObjA1::Builder& IObjA1::Builder::set_a(long a)
{
    return (IObjA1::Builder&)IObjA::Builder::set_a(a);
}

IObjRPtr IObjA1::clone(const IObj& object)
{
    return new IObjA1((const IObjA1&)object);
}

bool g_init_IObjA1 =
       IPluginObjFactory::registerCloneFunction(IObjA1::staticInprocId(), &IObjA1::clone)
    && IPluginObjFactory::registerRelationship (IObjA::staticInprocId(),  IObjA1::staticInprocId())
    && IPluginObjFactory::registerRelationship (IObj::staticInprocId(),   IObjA1::staticInprocId());

size_t IObjA1::staticInprocId()
{
    return (size_t)"factories.IObjA1";
}

size_t IObjA1::runtimeInprocId() const
{
    return staticInprocId();
}

long IObjA1::a1() const
{
    return mA1;
}

IObjA1::Builder& IObjA1::Builder::set_a1(long a1)
{
    ((IObjA1*)mpObject)->mA1 = a1;
    return *this;
}

IObjA2::Builder::Builder(IObjA2RPtr pObject)
        : IObjA::Builder(pObject)
{
}

IObjA2::Builder::~Builder()
{
    delete (IObjA2RPtr)mpObject;
    mpObject = NULL;
}

const IObjA2& IObjA2::Builder::build() const
{
    return *(IObjA2RPtr)mpObject;
}

IObjA2SPtr IObjA2::Builder::finalize()
{
    IObjA2RPtr objectRPtr = (IObjA2RPtr)mpObject;
    mpObject = NULL;
    return IObjA2SPtr(objectRPtr);
}

IObjA2::IObjA2()
{
}

IObjA2::~IObjA2()
{
}

IObjA2SPtr IObjA2::downcast(const IObjSPtr& object)
{
    return boost::static_pointer_cast<IObjA2>(object);
}

IObjA2::Builder& IObjA2::Builder::set_o(long o)
{
    return (IObjA2::Builder&)IObj::Builder::set_o(o);
}

IObjA2::Builder& IObjA2::Builder::set_inner(const EInner& inner)
{
    return (IObjA2::Builder&)IObj::Builder::set_inner(inner);
}

IObjA2::Builder& IObjA2::Builder::set_a(long a)
{
    return (IObjA2::Builder&)IObjA::Builder::set_a(a);
}

bool g_init_IObjA2 =
       IPluginObjFactory::registerRelationship(IObjA::staticInprocId(), IObjA2::staticInprocId())
    && IPluginObjFactory::registerRelationship(IObj::staticInprocId(),  IObjA2::staticInprocId());

size_t IObjA2::staticInprocId()
{
    return (size_t)"factories.IObjA2";
}

size_t IObjA2::runtimeInprocId() const
{
    return staticInprocId();
}

long IObjA2::a2() const
{
    return mA2;
}

IObjA2::Builder& IObjA2::Builder::set_a2(long a2)
{
    ((IObjA2*)mpObject)->mA2 = a2;
    return *this;
}

IObjB::Builder::Builder()
        : IObj::Builder(new IObjB())
{
}

IObjB::Builder::Builder(const IObjB& object)
        : IObj::Builder(IPluginObjFactory::clone<IObjB>(object))
{
}

IObjB::Builder::Builder(IObjBRPtr pObject)
        : IObj::Builder(pObject)
{
}

IObjB::Builder::~Builder()
{
    delete (IObjBRPtr)mpObject;
    mpObject = NULL;
}

const IObjB& IObjB::Builder::build() const
{
    return *(IObjBRPtr)mpObject;
}

IObjBSPtr IObjB::Builder::finalize()
{
    IObjBRPtr objectRPtr = (IObjBRPtr)mpObject;
    mpObject = NULL;
    return IObjBSPtr(objectRPtr);
}

IObjB::IObjB()
{
}

IObjB::~IObjB()
{
}

IObjBSPtr IObjB::downcast(const IObjSPtr& object)
{
    return boost::static_pointer_cast<IObjB>(object);
}

IObjB::Builder& IObjB::Builder::set_o(long o)
{
    return (IObjB::Builder&)IObj::Builder::set_o(o);
}

IObjB::Builder& IObjB::Builder::set_inner(const EInner& inner)
{
    return (IObjB::Builder&)IObj::Builder::set_inner(inner);
}

long IObjB::b() const
{
    return mB;
}

IObjB::Builder& IObjB::Builder::set_b(long b)
{
    ((IObjB*)mpObject)->mB = b;
    return *this;
}

IObjB1::Builder::Builder()
        : IObjB::Builder(new IObjB1())
{
}

IObjB1::Builder::Builder(const IObjB1& object)
        : IObjB::Builder(IPluginObjFactory::clone<IObjB1>(object))
{
}

IObjB1::Builder::Builder(IObjB1RPtr pObject)
        : IObjB::Builder(pObject)
{
}

IObjB1::Builder::~Builder()
{
    delete (IObjB1RPtr)mpObject;
    mpObject = NULL;
}

const IObjB1& IObjB1::Builder::build() const
{
    return *(IObjB1RPtr)mpObject;
}

IObjB1SPtr IObjB1::Builder::finalize()
{
    IObjB1RPtr objectRPtr = (IObjB1RPtr)mpObject;
    mpObject = NULL;
    return IObjB1SPtr(objectRPtr);
}

IObjB1::IObjB1()
{
}

IObjB1::~IObjB1()
{
}

IObjB1SPtr IObjB1::downcast(const IObjSPtr& object)
{
    return boost::static_pointer_cast<IObjB1>(object);
}

IObjB1::Builder& IObjB1::Builder::set_o(long o)
{
    return (IObjB1::Builder&)IObj::Builder::set_o(o);
}

IObjB1::Builder& IObjB1::Builder::set_inner(const EInner& inner)
{
    return (IObjB1::Builder&)IObj::Builder::set_inner(inner);
}

IObjB1::Builder& IObjB1::Builder::set_b(long b)
{
    return (IObjB1::Builder&)IObjB::Builder::set_b(b);
}

long IObjB1::b1() const
{
    return mB1;
}

IObjB1::Builder& IObjB1::Builder::set_b1(long b1)
{
    ((IObjB1*)mpObject)->mB1 = b1;
    return *this;
}

EIObjId::EIObjId()
        : mValue(kInvalid)
{
}

EIObjId::EIObjId(long value)
        : mValue(value)
{
}

const EIObjId EIObjId::invalid()
{
    return EIObjId(kInvalid);
}

const EIObjId EIObjId::iObj()
{
    return EIObjId(kIObj);
}

const EIObjId EIObjId::iObjA()
{
    return EIObjId(kIObjA);
}

const EIObjId EIObjId::iObjA2()
{
    return EIObjId(kIObjA2);
}

const EIObjId EIObjId::iObjB1()
{
    return EIObjId(kIObjB1);
}

long EIObjId::value() const
{
    return mValue;
}

const char* EIObjId::shortName(long value)
{
    static const char* names[] = 
    {
        "", // alignment
        "IObj",
        "IObjA",
        "IObjA2",
        "IObjB1",
    };
    return names[(size_t)value];
}

const char* EIObjId::shortName() const
{
    return shortName(value());
}

bool EIObjId::operator==(const EIObjId& rValue) const
{
    return mValue == rValue.mValue;
}

bool EIObjId::operator!=(const EIObjId& rValue) const
{
    return mValue != rValue.mValue;
}

EIObjId IObj::staticIObjId()
{
    return EIObjId::iObj();
}

EIObjId IObj::runtimeIObjId() const
{
    return staticIObjId();
}

EIObjId IObjA::staticIObjId()
{
    return EIObjId::iObjA();
}

EIObjId IObjA::runtimeIObjId() const
{
    return staticIObjId();
}

EIObjId IObjA2::staticIObjId()
{
    return EIObjId::iObjA2();
}

EIObjId IObjA2::runtimeIObjId() const
{
    return staticIObjId();
}

EIObjId IObjB1::staticIObjId()
{
    return EIObjId::iObjB1();
}

EIObjId IObjB1::runtimeIObjId() const
{
    return staticIObjId();
}

IObjSPtr HierarchyIObjFactory::clone(const IObjSPtr& pObject)
{
    switch (pObject->runtimeIObjId().value())
    {
        case EIObjId::kIObj:
        {
            IObjSPtr pClone(new IObj());
            *pClone = *pObject;
            return pClone;
        }
        case EIObjId::kIObjA:
        {
            IObjASPtr pClone(new IObjA());
            *pClone = *downcastIObjA(pObject);
            return pClone;
        }
        case EIObjId::kIObjB1:
        {
            IObjB1SPtr pClone(new IObjB1());
            *pClone = *downcastIObjB1(pObject);
            return pClone;
        }
        default:
            BOOST_ASSERT(false && "unknown objId");
    }
    return IObjSPtr();
}

IObjASPtr HierarchyIObjFactory::downcastIObjA(const IObjSPtr& pObject)
{
    bool b = (pObject->runtimeIObjId() == IObjA::staticIObjId())
          // or any of the derived classes
          || (pObject->runtimeIObjId() == IObjA2::staticIObjId());

    if (b)
        return boost::static_pointer_cast<IObjA>(pObject);
    return IObjASPtr();
}

IObjA2SPtr HierarchyIObjFactory::downcastIObjA2(const IObjSPtr& pObject)
{
    bool b = (pObject->runtimeIObjId() == IObjA2::staticIObjId());

    if (b)
        return boost::static_pointer_cast<IObjA2>(pObject);
    return IObjA2SPtr();
}

IObjB1SPtr HierarchyIObjFactory::downcastIObjB1(const IObjSPtr& pObject)
{
    bool b = (pObject->runtimeIObjId() == IObjB1::staticIObjId());

    if (b)
        return boost::static_pointer_cast<IObjB1>(pObject);
    return IObjB1SPtr();
}

MOObj::MOObj()
{
}

MOObj::~MOObj()
{
}

long MOObj::i() const
{
    return mI;
}

MOObj& MOObj::set_i(long i)
{
    mI = i;
    return *this;
}

long MOObj::o() const
{
    return mO;
}

MOObj& MOObj::set_o(long o)
{
    mO = o;
    return *this;
}

MOObj::EWeak::EWeak()
        : mValue(kInvalid)
{
}

MOObj::EWeak::EWeak(long value)
        : mValue(value)
{
}

const long MOObj::EWeak::invalid()
{
    return kInvalid;
}

const long MOObj::EWeak::value1()
{
    return kValue1;
}

const long MOObj::EWeak::value2()
{
    return kValue2;
}

long MOObj::EWeak::value() const
{
    return mValue;
}

const char* MOObj::EWeak::shortName(long value)
{
    static const char* names[] = 
    {
        "", // alignment
        "value1",
        "value2",
    };
    return names[(size_t)value];
}

const char* MOObj::EWeak::shortName() const
{
    return shortName(value());
}

MOObj::EWeak::operator long () const
{
    return mValue;
}

MOObj::EStrong::EStrong()
        : mValue(kInvalid)
{
}

MOObj::EStrong::EStrong(long value)
        : mValue(value)
{
}

const MOObj::EStrong MOObj::EStrong::invalid()
{
    return EStrong(kInvalid);
}

const MOObj::EStrong MOObj::EStrong::value1()
{
    return EStrong(kValue1);
}

const MOObj::EStrong MOObj::EStrong::value2()
{
    return EStrong(kValue2);
}

long MOObj::EStrong::value() const
{
    return mValue;
}

const char* MOObj::EStrong::shortName(long value)
{
    static const char* names[] = 
    {
        "", // alignment
        "value1",
        "value2",
    };
    return names[(size_t)value];
}

const char* MOObj::EStrong::shortName() const
{
    return shortName(value());
}

bool MOObj::EStrong::operator==(const EStrong& rValue) const
{
    return mValue == rValue.mValue;
}

bool MOObj::EStrong::operator!=(const EStrong& rValue) const
{
    return mValue != rValue.mValue;
}

const MOObj::EWeak& MOObj::w() const
{
    return mW;
}

MOObj& MOObj::set_w(const EWeak& w)
{
    mW = w;
    return *this;
}

MOObj::EWeak& MOObj::mutable_w()
{
    return mW;
}

const MOObj::EStrong& MOObj::s() const
{
    return mS;
}

MOObj& MOObj::set_s(const EStrong& s)
{
    mS = s;
    return *this;
}

MOObj::EStrong& MOObj::mutable_s()
{
    return mS;
}

MOObjSPtr MObjectObjFactory::create(long i, const MOObj::EWeak& w, const MOObj::EStrong& s)
{
    MOObjSPtr pObj(new MOObj());
    pObj->set_i(i);
    pObj->set_w(w);
    pObj->set_s(s);
    return pObj;
}

MOObjSPtr MObjectObjFactory::create(long i, long o, const MOObj::EWeak& w, const MOObj::EStrong& s)
{
    MOObjSPtr pObj(new MOObj());
    pObj->set_i(i);
    pObj->set_o(o);
    pObj->set_w(w);
    pObj->set_s(s);
    return pObj;
}

MOObjSPtr CreateMObjectObj(long i, const MOObj::EWeak& w, const MOObj::EStrong& s)
{
    MOObjSPtr pObj(new MOObj());
    pObj->set_i(i);
    pObj->set_w(w);
    pObj->set_s(s);
    return pObj;
}

MOObjSPtr CreateMObjectObj(long i, long o, const MOObj::EWeak& w, const MOObj::EStrong& s)
{
    MOObjSPtr pObj(new MOObj());
    pObj->set_i(i);
    pObj->set_o(o);
    pObj->set_w(w);
    pObj->set_s(s);
    return pObj;
}

IMOObj::Builder::Builder()
        : mpObject(new IMOObj())
{
}

IMOObj::Builder::Builder(const IMOObj& object)
        : mpObject(new IMOObj())
{
    *(IMOObj*)mpObject = object;
}

IMOObj::Builder::Builder(IMOObjRPtr pObject)
        : mpObject(pObject)
{
}

IMOObj::Builder::~Builder()
{
    delete (IMOObjRPtr)mpObject;
    mpObject = NULL;
}

const IMOObj& IMOObj::Builder::build() const
{
    return *(IMOObjRPtr)mpObject;
}

IMOObjSPtr IMOObj::Builder::finalize()
{
    IMOObjRPtr objectRPtr = (IMOObjRPtr)mpObject;
    mpObject = NULL;
    return IMOObjSPtr(objectRPtr);
}

IMOObj::IMOObj()
{
}

IMOObj::~IMOObj()
{
}

unsigned char IMOObj::i() const
{
    return mI;
}

IMOObj::Builder& IMOObj::Builder::set_i(unsigned char i)
{
    mpObject->mI = i;
    return *this;
}

unsigned short IMOObj::o() const
{
    return mO;
}

IMOObj::Builder& IMOObj::Builder::set_o(unsigned short o)
{
    mpObject->mO = o;
    return *this;
}

IMOObjSPtr IMObjectObjFactory::create(unsigned char i)
{
    IMOObj::Builder builder;
    builder.set_i(i);
    return builder.finalize();
}

IMOObjSPtr IMObjectObjFactory::create(unsigned char i, unsigned short o)
{
    IMOObj::Builder builder;
    builder.set_i(i);
    builder.set_o(o);
    return builder.finalize();
}

IMOObj2::Builder::Builder()
        : IMOObj::Builder(new IMOObj2())
{
}

IMOObj2::Builder::Builder(const IMOObj2& object)
        : IMOObj::Builder(new IMOObj2())
{
    *(IMOObj2*)mpObject = object;
}

IMOObj2::Builder::Builder(IMOObj2RPtr pObject)
        : IMOObj::Builder(pObject)
{
}

IMOObj2::Builder::~Builder()
{
    delete (IMOObj2RPtr)mpObject;
    mpObject = NULL;
}

const IMOObj2& IMOObj2::Builder::build() const
{
    return *(IMOObj2RPtr)mpObject;
}

IMOObj2SPtr IMOObj2::Builder::finalize()
{
    IMOObj2RPtr objectRPtr = (IMOObj2RPtr)mpObject;
    mpObject = NULL;
    return IMOObj2SPtr(objectRPtr);
}

IMOObj2::IMOObj2()
{
}

IMOObj2::~IMOObj2()
{
}

IMOObj2SPtr IMOObj2::downcast(const IMOObjSPtr& object)
{
    return boost::static_pointer_cast<IMOObj2>(object);
}

IMOObj2::Builder& IMOObj2::Builder::set_i(unsigned char i)
{
    return (IMOObj2::Builder&)IMOObj::Builder::set_i(i);
}

IMOObj2::Builder& IMOObj2::Builder::set_o(unsigned short o)
{
    return (IMOObj2::Builder&)IMOObj::Builder::set_o(o);
}

unsigned long IMOObj2::i2() const
{
    return mI2;
}

IMOObj2::Builder& IMOObj2::Builder::set_i2(unsigned long i2)
{
    ((IMOObj2*)mpObject)->mI2 = i2;
    return *this;
}

unsigned long long IMOObj2::o2() const
{
    return mO2;
}

IMOObj2::Builder& IMOObj2::Builder::set_o2(unsigned long long o2)
{
    ((IMOObj2*)mpObject)->mO2 = o2;
    return *this;
}

IMOObj2SPtr IMObjectObj2Factory::create(unsigned char i, unsigned long i2)
{
    IMOObj2::Builder builder;
    builder.set_i(i);
    builder.set_i2(i2);
    return builder.finalize();
}

IMOObj2SPtr IMObjectObj2Factory::create(unsigned char i, unsigned short o, unsigned long i2)
{
    IMOObj2::Builder builder;
    builder.set_i(i);
    builder.set_o(o);
    builder.set_i2(i2);
    return builder.finalize();
}

IMOObj2SPtr IMObjectObj2Factory::create(unsigned char i, unsigned long i2, unsigned long long o2)
{
    IMOObj2::Builder builder;
    builder.set_i(i);
    builder.set_i2(i2);
    builder.set_o2(o2);
    return builder.finalize();
}

IMOObj2SPtr IMObjectObj2Factory::create(unsigned char i, unsigned short o, unsigned long i2, unsigned long long o2)
{
    IMOObj2::Builder builder;
    builder.set_i(i);
    builder.set_o(o);
    builder.set_i2(i2);
    builder.set_o2(o2);
    return builder.finalize();
}

}

