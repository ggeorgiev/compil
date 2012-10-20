// Boost C++ Smart Pointers
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
// Boost C++ Utility
#include <boost/assert.hpp>

#ifndef __GENERATOR_TEST_FACTORIES_COMPIL_H_
#define __GENERATOR_TEST_FACTORIES_COMPIL_H_

#include "factories.h"
// Boost C++ Unordered
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
// Standard Template Library
#include <utility>

namespace factories
{

class ObjBase
{
public:
    // Default constructor
            ObjBase ();
    // Destructor
    /*lax*/ ~ObjBase();

    // This enumeration class provides namespaced set of constant values.
    // It is designed to provide type control over operations with enum
    // values without need to wait all compilers you are going to use for
    // this project to support C++0x standard. The type control do not
    // prevent the variables to be used in switch statements.
    class EInnerBase
    {
    public:
        // Default constructor - sets the value to invalid
                             EInnerBase();
        // Constructor from an integer value.
        // Note: Avoid using this constructor if possible. It is
        // appropriate only in case of importing value from components that
        // you do not have control over (such as 3rd party libraries or
        // serialization functionality).
        explicit             EInnerBase(long value);

        // Returns the integer value of the enum.
        // Note: Avoid using this method if possible. It is appropriate
        // only in case of exporting value to components that you do not
        // have control over (such as 3rd party libraries or serialization
        // functionality).
                 long        value     ()                         const;
        // Returns short name for a specified enum value
        static   const char* shortName (long value);
        // Returns short name of the enum value
                 const char* shortName ()                         const;
        // returns true if the value of the enum is equal to the value of
        // the argument
                 bool        operator==(const EInnerBase& rValue) const;
        // returns true if the value of the enum is not equal to the value
        // of the argument
                 bool        operator!=(const EInnerBase& rValue) const;

        // static methods for enum class objects
        static const EInnerBase invalid();

        // This enum provides static constants that could be used in a
        // switch statements
        enum
        {
            kInvalid = 0,
        };

    private:
        // Member variable that holds the enum value
        long mValue;
    };


    // Inproc identifier for the objects from ObjBase class.
    // Note: this identificator is unique just for the process session.
    // There is no guarantee that the id will be the same from session to
    // session. Do not use for serialization.
    static  size_t            staticInprocId   ();
    // This virtual method provides runtime inproc object identification
    // based on the polymorphic behavior of the virtual methods. Allows
    // having a RTTI like mechanism significantly cheaper than the RTTI
    // provided by the compilers themselves.
    virtual size_t            runtimeInprocId  ()                            const;

    // Getter method for the data field innerBase
            const EInnerBase& innerBase        ()                            const;
    // Setter method for the data field innerBase
            ObjBase&          set_innerBase    (const EInnerBase& innerBase);
    // Provides mutable access to field innerBase
            EInnerBase&       mutable_innerBase();

private:
    // variable for the data field innerBase
    EInnerBase mInnerBase;
};

// IObjBase is an immutable class - once instantiated none of the data
// fields can be changed. For the initial initialization and instantiation
// use the nested Builder class.

// Immutability is useful in multi-thread and subject observer
// applications. It makes easy creation of models with object references.

class IObjBase
{
public:
    class EInnerBase;

    // Use Builder to instantiate objects
    class Builder
    {
        // hide evil auto created assignment operator, no implementation
                void            operator=        (const Builder& );
    public:
        // Default constructor. All fields without default values are left
        // uninitialized. Make sure you initialize all the necessary fields
        // before instantiating
                                Builder          ();
        // Use this constructor when you need to clone or create an object
        // just slightly different from another object
                                Builder          (const IObjBase& object);
        // Destructor of Builder
        /*lax*/                 ~Builder         ();

        // Instantiates IObjBase instance with the current initialization
        // of the fields. After the instance is ready the builder could be
        // reused to instantiate more objects. The data is not reset.
        // Second call of build() will instantiate object with the same
        // data.
                const IObjBase& build            ()                            const;

        // Provides the internal instantiated builder object and
        // invalidates the builder status. Once finalize() is called, the
        // builder can not be used again. Use finalize() when you no longer
        // are going to use this builder.
                IObjBaseSPtr    finalize         ();


        // Setter method for the data field innerBase
                Builder&        set_innerBase    (const EInnerBase& innerBase);
        // Provides mutable access to field innerBase
                EInnerBase&     mutable_innerBase();

    protected:
        // constructor needed from potential derived classes
                                Builder          (IObjBaseRPtr pObject);

        IObjBaseRPtr mpObject;
    };

    // Default constructor
            IObjBase ();
    // Destructor
    /*lax*/ ~IObjBase();

    // This enumeration class provides namespaced set of constant values.
    // It is designed to provide type control over operations with enum
    // values without need to wait all compilers you are going to use for
    // this project to support C++0x standard. The type control do not
    // prevent the variables to be used in switch statements.
    class EInnerBase
    {
    public:
        // Default constructor - sets the value to invalid
                             EInnerBase();
        // Constructor from an integer value.
        // Note: Avoid using this constructor if possible. It is
        // appropriate only in case of importing value from components that
        // you do not have control over (such as 3rd party libraries or
        // serialization functionality).
        explicit             EInnerBase(long value);

        // Returns the integer value of the enum.
        // Note: Avoid using this method if possible. It is appropriate
        // only in case of exporting value to components that you do not
        // have control over (such as 3rd party libraries or serialization
        // functionality).
                 long        value     ()                         const;
        // Returns short name for a specified enum value
        static   const char* shortName (long value);
        // Returns short name of the enum value
                 const char* shortName ()                         const;
        // returns true if the value of the enum is equal to the value of
        // the argument
                 bool        operator==(const EInnerBase& rValue) const;
        // returns true if the value of the enum is not equal to the value
        // of the argument
                 bool        operator!=(const EInnerBase& rValue) const;

        // static methods for enum class objects
        static const EInnerBase invalid();

        // This enum provides static constants that could be used in a
        // switch statements
        enum
        {
            kInvalid = 0,
        };

    private:
        // Member variable that holds the enum value
        long mValue;
    };


    // Inproc identifier for the objects from IObjBase class.
    // Note: this identificator is unique just for the process session.
    // There is no guarantee that the id will be the same from session to
    // session. Do not use for serialization.
    static  size_t            staticInprocId ();
    // This virtual method provides runtime inproc object identification
    // based on the polymorphic behavior of the virtual methods. Allows
    // having a RTTI like mechanism significantly cheaper than the RTTI
    // provided by the compilers themselves.
    virtual size_t            runtimeInprocId() const;

    // Getter method for the data field innerBase
            const EInnerBase& innerBase      () const;

private:
    // variable for the data field innerBase
    EInnerBase mInnerBase;
};

class Obj
{
public:
    // Default constructor
            Obj ();
    // Destructor
    virtual ~Obj();

    // This enumeration class provides namespaced set of constant values.
    // It is designed to provide type control over operations with enum
    // values without need to wait all compilers you are going to use for
    // this project to support C++0x standard. The type control do not
    // prevent the variables to be used in switch statements.
    class EInner
    {
    public:
        // Default constructor - sets the value to invalid
                             EInner    ();
        // Constructor from an integer value.
        // Note: Avoid using this constructor if possible. It is
        // appropriate only in case of importing value from components that
        // you do not have control over (such as 3rd party libraries or
        // serialization functionality).
        explicit             EInner    (long value);

        // Returns the integer value of the enum.
        // Note: Avoid using this method if possible. It is appropriate
        // only in case of exporting value to components that you do not
        // have control over (such as 3rd party libraries or serialization
        // functionality).
                 long        value     ()                     const;
        // Returns short name for a specified enum value
        static   const char* shortName (long value);
        // Returns short name of the enum value
                 const char* shortName ()                     const;
        // returns true if the value of the enum is equal to the value of
        // the argument
                 bool        operator==(const EInner& rValue) const;
        // returns true if the value of the enum is not equal to the value
        // of the argument
                 bool        operator!=(const EInner& rValue) const;

        // static methods for enum class objects
        static const EInner invalid();

        // This enum provides static constants that could be used in a
        // switch statements
        enum
        {
            kInvalid = 0,
        };

    private:
        // Member variable that holds the enum value
        long mValue;
    };


    // Identifier for the objects from Obj class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EObjId        staticObjId    ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EObjId        runtimeObjId   ()                    const;

    // Static clone method that implements the plugin factory
    // PluginObjFactory clone function prototype. It will be registered in
    // the factory for potential use from its clone method. Most likely you
    // will never need to use this method from anywhere else.
    static  ObjRPtr       clone          (const Obj& object);
    // Inproc identifier for the objects from Obj class.
    // Note: this identificator is unique just for the process session.
    // There is no guarantee that the id will be the same from session to
    // session. Do not use for serialization.
    static  size_t        staticInprocId ();
    // This virtual method provides runtime inproc object identification
    // based on the polymorphic behavior of the virtual methods. Allows
    // having a RTTI like mechanism significantly cheaper than the RTTI
    // provided by the compilers themselves.
    virtual size_t        runtimeInprocId()                    const;

    // Getter method for the data field o
            long          o              ()                    const;
    // Setter method for the data field o
            Obj&          set_o          (long o);

    // Getter method for the data field inner
            const EInner& inner          ()                    const;
    // Setter method for the data field inner
            Obj&          set_inner      (const EInner& inner);
    // Provides mutable access to field inner
            EInner&       mutable_inner  ();

private:
    // variable for the data field o
    long   mO;
    // variable for the data field inner
    EInner mInner;
};

// This class is a plugin object factory designed to provide functionality
// for objects from several layers without creating explicit dependency on
// all of them. It is designed to be initialized from the CRT
// initialization process and used read only application runtime. This is
// why it does not provide any additional thread safety. If needed for
// other scenarios, the thread safety needs to be provided from outside.
class PluginObjFactory
{
public:
    // Clone function pointer type
    typedef ObjRPtr (*fnClone)(const Obj&object);
    // Relationship pair<parent, child> type
    typedef std::pair<size_t, size_t> Pair;

    // Default constructor
                             PluginObjFactory     ();
    // Destructor

                             ~PluginObjFactory    ();

    // Register clone function method. Use to register objects that the
    // factory needs to support
    static bool              registerCloneFunction(size_t object, fnClone function);

    // Register relationship method. Use to register relationships between
    // objects.
    static bool              registerRelationship (size_t parent, size_t child);
    // Returns is the parent/child pair is registered in the factory.
    static bool              isParent             (size_t parent, size_t child);

    // Clone template method based on already registered objects. This
    // allows objects from upper layer to be cloned correctly producing
    // clone object from the same class as the original object without
    // creating circular dependency.
    template<class T>
    static T*                clone                (const T& object)
    {
        BOOST_ASSERT(isDerivedFrom<T>(object));
        return (T*)get().cloneFunctions[object.runtimeInprocId()](object);
    }

    // IsDerivedFrom template method returns true based on already
    // registered objects if the argument object is from the same class or
    // a derived one from the argument class.
    template<class T>
    static bool              isDerivedFrom        (const Obj& object)
    {
        return (T::staticInprocId() == object.runtimeInprocId())
                || isParent(T::staticInprocId(), object.runtimeInprocId());
    }
    // The same as previous one. Just a helper that accepts pointer instead
    // of an object.
    template<class T>
    static bool              isDerivedFrom        (const ObjSPtr& object)
    {
        return isDerivedFrom<T>(*object);
    }

protected:
    // Global singleton accessor.
    static PluginObjFactory& get                  ();

    // Member variable for clone functions.
    boost::unordered_map<size_t, fnClone> cloneFunctions;
    // Member variable for relationship pairs.
    boost::unordered_set<Pair>            relationships;
};

class ObjA : public Obj
{
public:
    // Default constructor
                     ObjA           ();
    // Destructor
    virtual          ~ObjA          ();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  ObjASPtr downcast       (const ObjSPtr& object);

    // Identifier for the objects from ObjA class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EObjId   staticObjId    ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EObjId   runtimeObjId   ()                      const;

    // Static clone method that implements the plugin factory
    // PluginObjFactory clone function prototype. It will be registered in
    // the factory for potential use from its clone method. Most likely you
    // will never need to use this method from anywhere else.
    static  ObjRPtr  clone          (const Obj& object);
    // Inproc identifier for the objects from ObjA class.
    // Note: this identificator is unique just for the process session.
    // There is no guarantee that the id will be the same from session to
    // session. Do not use for serialization.
    static  size_t   staticInprocId ();
    // This virtual method provides runtime inproc object identification
    // based on the polymorphic behavior of the virtual methods. Allows
    // having a RTTI like mechanism significantly cheaper than the RTTI
    // provided by the compilers themselves.
    virtual size_t   runtimeInprocId()                      const;

    // Getter method for the data field a
            long     a              ()                      const;
    // Setter method for the data field a
            ObjA&    set_a          (long a);

private:
    // variable for the data field a
    long mA;
};

class ObjA1 : public ObjA
{
public:
    // Default constructor
                      ObjA1          ();
    // Destructor
    virtual           ~ObjA1         ();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  ObjA1SPtr downcast       (const ObjSPtr& object);

    // Static clone method that implements the plugin factory
    // PluginObjFactory clone function prototype. It will be registered in
    // the factory for potential use from its clone method. Most likely you
    // will never need to use this method from anywhere else.
    static  ObjRPtr   clone          (const Obj& object);
    // Inproc identifier for the objects from ObjA1 class.
    // Note: this identificator is unique just for the process session.
    // There is no guarantee that the id will be the same from session to
    // session. Do not use for serialization.
    static  size_t    staticInprocId ();
    // This virtual method provides runtime inproc object identification
    // based on the polymorphic behavior of the virtual methods. Allows
    // having a RTTI like mechanism significantly cheaper than the RTTI
    // provided by the compilers themselves.
    virtual size_t    runtimeInprocId()                      const;

    // Getter method for the data field a1
            long      a1             ()                      const;
    // Setter method for the data field a1
            ObjA1&    set_a1         (long a1);

private:
    // variable for the data field a1
    long mA1;
};

class ObjA2 : public ObjA
{
public:
    // Default constructor
                      ObjA2          ();
    // Destructor
    virtual           ~ObjA2         ();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  ObjA2SPtr downcast       (const ObjSPtr& object);

    // Identifier for the objects from ObjA2 class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EObjId    staticObjId    ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EObjId    runtimeObjId   ()                      const;

    // Inproc identifier for the objects from ObjA2 class.
    // Note: this identificator is unique just for the process session.
    // There is no guarantee that the id will be the same from session to
    // session. Do not use for serialization.
    static  size_t    staticInprocId ();
    // This virtual method provides runtime inproc object identification
    // based on the polymorphic behavior of the virtual methods. Allows
    // having a RTTI like mechanism significantly cheaper than the RTTI
    // provided by the compilers themselves.
    virtual size_t    runtimeInprocId()                      const;

    // Getter method for the data field a2
            long      a2             ()                      const;
    // Setter method for the data field a2
            ObjA2&    set_a2         (long a2);

private:
    // variable for the data field a2
    long mA2;
};

class ObjB : public Obj
{
public:
    // Default constructor
                     ObjB    ();
    // Destructor
    virtual          ~ObjB   ();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  ObjBSPtr downcast(const ObjSPtr& object);

    // Getter method for the data field b
            long     b       ()                      const;
    // Setter method for the data field b
            ObjB&    set_b   (long b);

private:
    // variable for the data field b
    long mB;
};

class ObjB1 : public ObjB
{
public:
    // Default constructor
                      ObjB1       ();
    // Destructor
    virtual           ~ObjB1      ();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  ObjB1SPtr downcast    (const ObjSPtr& object);

    // Identifier for the objects from ObjB1 class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EObjId    staticObjId ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EObjId    runtimeObjId()                      const;

    // Getter method for the data field b1
            long      b1          ()                      const;
    // Setter method for the data field b1
            ObjB1&    set_b1      (long b1);

private:
    // variable for the data field b1
    long mB1;
};

// This enumeration class provides namespaced set of constant values.
// It is designed to provide type control over operations with enum values
// without need to wait all compilers you are going to use for this project
// to support C++0x standard. The type control do not prevent the variables
// to be used in switch statements.
class EObjId
{
public:
    // Default constructor - sets the value to invalid
                         EObjId    ();
    // Constructor from an integer value.
    // Note: Avoid using this constructor if possible. It is appropriate
    // only in case of importing value from components that you do not have
    // control over (such as 3rd party libraries or serialization
    // functionality).
    explicit             EObjId    (long value);

    // Returns the integer value of the enum.
    // Note: Avoid using this method if possible. It is appropriate only in
    // case of exporting value to components that you do not have control
    // over (such as 3rd party libraries or serialization functionality).
             long        value     ()                     const;
    // Returns short name for a specified enum value
    static   const char* shortName (long value);
    // Returns short name of the enum value
             const char* shortName ()                     const;
    // returns true if the value of the enum is equal to the value of the
    // argument
             bool        operator==(const EObjId& rValue) const;
    // returns true if the value of the enum is not equal to the value of
    // the argument
             bool        operator!=(const EObjId& rValue) const;

    // static methods for enum class objects
    static const EObjId invalid();
    static const EObjId obj    ();
    static const EObjId objA   ();
    static const EObjId objA2  ();
    static const EObjId objB1  ();

    // This enum provides static constants that could be used in a switch
    // statements
    enum
    {
        kInvalid = 0,
        kObj     = 1,
        kObjA    = 2,
        kObjA2   = 3,
        kObjB1   = 4,
    };

private:
    // Member variable that holds the enum value
    long mValue;
};

class HierarchyObjFactory
{
public:
    static ObjSPtr   clone        (const ObjSPtr& object);
    static ObjASPtr  downcastObjA (const ObjSPtr& object);
    static ObjA2SPtr downcastObjA2(const ObjSPtr& object);
    static ObjB1SPtr downcastObjB1(const ObjSPtr& object);
};

// IObj is an immutable class - once instantiated none of the data fields
// can be changed. For the initial initialization and instantiation use the
// nested Builder class.

// Immutability is useful in multi-thread and subject observer
// applications. It makes easy creation of models with object references.

class IObj
{
public:
    class EInner;

    // Use Builder to instantiate objects
    class Builder
    {
        // hide evil auto created assignment operator, no implementation
                void        operator=    (const Builder& );
    public:
        // Default constructor. All fields without default values are left
        // uninitialized. Make sure you initialize all the necessary fields
        // before instantiating
                            Builder      ();
        // Use this constructor when you need to clone or create an object
        // just slightly different from another object
                            Builder      (const IObj& object);
        // Destructor of Builder
        /*lax*/             ~Builder     ();

        // Instantiates IObj instance with the current initialization of
        // the fields. After the instance is ready the builder could be
        // reused to instantiate more objects. The data is not reset.
        // Second call of build() will instantiate object with the same
        // data.
                const IObj& build        ()                    const;

        // Provides the internal instantiated builder object and
        // invalidates the builder status. Once finalize() is called, the
        // builder can not be used again. Use finalize() when you no longer
        // are going to use this builder.
                IObjSPtr    finalize     ();


        // Setter method for the data field o
                Builder&    set_o        (long o);

        // Setter method for the data field inner
                Builder&    set_inner    (const EInner& inner);
        // Provides mutable access to field inner
                EInner&     mutable_inner();

    protected:
        // constructor needed from potential derived classes
                            Builder      (IObjRPtr pObject);

        IObjRPtr mpObject;
    };

    // Default constructor
            IObj ();
    // Destructor
    virtual ~IObj();

    // This enumeration class provides namespaced set of constant values.
    // It is designed to provide type control over operations with enum
    // values without need to wait all compilers you are going to use for
    // this project to support C++0x standard. The type control do not
    // prevent the variables to be used in switch statements.
    class EInner
    {
    public:
        // Default constructor - sets the value to invalid
                             EInner    ();
        // Constructor from an integer value.
        // Note: Avoid using this constructor if possible. It is
        // appropriate only in case of importing value from components that
        // you do not have control over (such as 3rd party libraries or
        // serialization functionality).
        explicit             EInner    (long value);

        // Returns the integer value of the enum.
        // Note: Avoid using this method if possible. It is appropriate
        // only in case of exporting value to components that you do not
        // have control over (such as 3rd party libraries or serialization
        // functionality).
                 long        value     ()                     const;
        // Returns short name for a specified enum value
        static   const char* shortName (long value);
        // Returns short name of the enum value
                 const char* shortName ()                     const;
        // returns true if the value of the enum is equal to the value of
        // the argument
                 bool        operator==(const EInner& rValue) const;
        // returns true if the value of the enum is not equal to the value
        // of the argument
                 bool        operator!=(const EInner& rValue) const;

        // static methods for enum class objects
        static const EInner invalid();

        // This enum provides static constants that could be used in a
        // switch statements
        enum
        {
            kInvalid = 0,
        };

    private:
        // Member variable that holds the enum value
        long mValue;
    };


    // Identifier for the objects from IObj class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EIObjId       staticIObjId   ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EIObjId       runtimeIObjId  ()                   const;

    // Static clone method that implements the plugin factory
    // IPluginObjFactory clone function prototype. It will be registered in
    // the factory for potential use from its clone method. Most likely you
    // will never need to use this method from anywhere else.
    static  IObjRPtr      clone          (const IObj& object);
    // Inproc identifier for the objects from IObj class.
    // Note: this identificator is unique just for the process session.
    // There is no guarantee that the id will be the same from session to
    // session. Do not use for serialization.
    static  size_t        staticInprocId ();
    // This virtual method provides runtime inproc object identification
    // based on the polymorphic behavior of the virtual methods. Allows
    // having a RTTI like mechanism significantly cheaper than the RTTI
    // provided by the compilers themselves.
    virtual size_t        runtimeInprocId()                   const;

    // Getter method for the data field o
            long          o              ()                   const;

    // Getter method for the data field inner
            const EInner& inner          ()                   const;

private:
    // variable for the data field o
    long   mO;
    // variable for the data field inner
    EInner mInner;
};

// This class is a plugin object factory designed to provide functionality
// for objects from several layers without creating explicit dependency on
// all of them. It is designed to be initialized from the CRT
// initialization process and used read only application runtime. This is
// why it does not provide any additional thread safety. If needed for
// other scenarios, the thread safety needs to be provided from outside.
class IPluginObjFactory
{
public:
    // Clone function pointer type
    typedef IObjRPtr (*fnClone)(const IObj&object);
    // Relationship pair<parent, child> type
    typedef std::pair<size_t, size_t> Pair;

    // Default constructor
                              IPluginObjFactory    ();
    // Destructor

                              ~IPluginObjFactory   ();

    // Register clone function method. Use to register objects that the
    // factory needs to support
    static bool               registerCloneFunction(size_t object, fnClone function);

    // Register relationship method. Use to register relationships between
    // objects.
    static bool               registerRelationship (size_t parent, size_t child);
    // Returns is the parent/child pair is registered in the factory.
    static bool               isParent             (size_t parent, size_t child);

    // Clone template method based on already registered objects. This
    // allows objects from upper layer to be cloned correctly producing
    // clone object from the same class as the original object without
    // creating circular dependency.
    template<class T>
    static T*                 clone                (const T& object)
    {
        BOOST_ASSERT(isDerivedFrom<T>(object));
        return (T*)get().cloneFunctions[object.runtimeInprocId()](object);
    }

    // IsDerivedFrom template method returns true based on already
    // registered objects if the argument object is from the same class or
    // a derived one from the argument class.
    template<class T>
    static bool               isDerivedFrom        (const IObj& object)
    {
        return (T::staticInprocId() == object.runtimeInprocId())
                || isParent(T::staticInprocId(), object.runtimeInprocId());
    }
    // The same as previous one. Just a helper that accepts pointer instead
    // of an object.
    template<class T>
    static bool               isDerivedFrom        (const IObjSPtr& object)
    {
        return isDerivedFrom<T>(*object);
    }

protected:
    // Global singleton accessor.
    static IPluginObjFactory& get                  ();

    // Member variable for clone functions.
    boost::unordered_map<size_t, fnClone> cloneFunctions;
    // Member variable for relationship pairs.
    boost::unordered_set<Pair>            relationships;
};

// IObjA is an immutable class - once instantiated none of the data fields
// can be changed. For the initial initialization and instantiation use the
// nested Builder class.

// Immutability is useful in multi-thread and subject observer
// applications. It makes easy creation of models with object references.

class IObjA : public IObj
{
public:
    // Use Builder to instantiate objects
    class Builder : public IObj::Builder
    {
        // hide evil auto created assignment operator, no implementation
                void         operator=(const Builder& );
    public:
        // Default constructor. All fields without default values are left
        // uninitialized. Make sure you initialize all the necessary fields
        // before instantiating
                             Builder  ();
        // Use this constructor when you need to clone or create an object
        // just slightly different from another object
                             Builder  (const IObjA& object);
        // Destructor of Builder
        /*lax*/              ~Builder ();

        // Instantiates IObjA instance with the current initialization of
        // the fields. After the instance is ready the builder could be
        // reused to instantiate more objects. The data is not reset.
        // Second call of build() will instantiate object with the same
        // data.
                const IObjA& build    ()                    const;

        // Provides the internal instantiated builder object and
        // invalidates the builder status. Once finalize() is called, the
        // builder can not be used again. Use finalize() when you no longer
        // are going to use this builder.
                IObjASPtr    finalize ();


        // Setter method for the data field o
                Builder&     set_o    (long o);

        // Setter method for the data field inner
                Builder&     set_inner(const EInner& inner);

        // Setter method for the data field a
                Builder&     set_a    (long a);

    protected:
        // constructor needed from potential derived classes
                             Builder  (IObjARPtr pObject);
    };

    // Default constructor
                      IObjA          ();
    // Destructor
    virtual           ~IObjA         ();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  IObjASPtr downcast       (const IObjSPtr& object);

    // Identifier for the objects from IObjA class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EIObjId   staticIObjId   ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EIObjId   runtimeIObjId  ()                       const;

    // Static clone method that implements the plugin factory
    // IPluginObjFactory clone function prototype. It will be registered in
    // the factory for potential use from its clone method. Most likely you
    // will never need to use this method from anywhere else.
    static  IObjRPtr  clone          (const IObj& object);
    // Inproc identifier for the objects from IObjA class.
    // Note: this identificator is unique just for the process session.
    // There is no guarantee that the id will be the same from session to
    // session. Do not use for serialization.
    static  size_t    staticInprocId ();
    // This virtual method provides runtime inproc object identification
    // based on the polymorphic behavior of the virtual methods. Allows
    // having a RTTI like mechanism significantly cheaper than the RTTI
    // provided by the compilers themselves.
    virtual size_t    runtimeInprocId()                       const;

    // Getter method for the data field a
            long      a              ()                       const;

private:
    // variable for the data field a
    long mA;
};

// IObjA1 is an immutable class - once instantiated none of the data fields
// can be changed. For the initial initialization and instantiation use the
// nested Builder class.

// Immutability is useful in multi-thread and subject observer
// applications. It makes easy creation of models with object references.

class IObjA1 : public IObjA
{
public:
    // Use Builder to instantiate objects
    class Builder : public IObjA::Builder
    {
        // hide evil auto created assignment operator, no implementation
                void          operator=(const Builder& );
    public:
        // Default constructor. All fields without default values are left
        // uninitialized. Make sure you initialize all the necessary fields
        // before instantiating
                              Builder  ();
        // Use this constructor when you need to clone or create an object
        // just slightly different from another object
                              Builder  (const IObjA1& object);
        // Destructor of Builder
        /*lax*/               ~Builder ();

        // Instantiates IObjA1 instance with the current initialization of
        // the fields. After the instance is ready the builder could be
        // reused to instantiate more objects. The data is not reset.
        // Second call of build() will instantiate object with the same
        // data.
                const IObjA1& build    ()                     const;

        // Provides the internal instantiated builder object and
        // invalidates the builder status. Once finalize() is called, the
        // builder can not be used again. Use finalize() when you no longer
        // are going to use this builder.
                IObjA1SPtr    finalize ();


        // Setter method for the data field o
                Builder&      set_o    (long o);

        // Setter method for the data field inner
                Builder&      set_inner(const EInner& inner);

        // Setter method for the data field a
                Builder&      set_a    (long a);

        // Setter method for the data field a1
                Builder&      set_a1   (long a1);

    protected:
        // constructor needed from potential derived classes
                              Builder  (IObjA1RPtr pObject);
    };

    // Default constructor
                       IObjA1         ();
    // Destructor
    virtual            ~IObjA1        ();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  IObjA1SPtr downcast       (const IObjSPtr& object);

    // Static clone method that implements the plugin factory
    // IPluginObjFactory clone function prototype. It will be registered in
    // the factory for potential use from its clone method. Most likely you
    // will never need to use this method from anywhere else.
    static  IObjRPtr   clone          (const IObj& object);
    // Inproc identifier for the objects from IObjA1 class.
    // Note: this identificator is unique just for the process session.
    // There is no guarantee that the id will be the same from session to
    // session. Do not use for serialization.
    static  size_t     staticInprocId ();
    // This virtual method provides runtime inproc object identification
    // based on the polymorphic behavior of the virtual methods. Allows
    // having a RTTI like mechanism significantly cheaper than the RTTI
    // provided by the compilers themselves.
    virtual size_t     runtimeInprocId()                       const;

    // Getter method for the data field a1
            long       a1             ()                       const;

private:
    // variable for the data field a1
    long mA1;
};

// IObjA2 is an immutable class - once instantiated none of the data fields
// can be changed. For the initial initialization and instantiation use the
// nested Builder class.

// Immutability is useful in multi-thread and subject observer
// applications. It makes easy creation of models with object references.

class IObjA2 : public IObjA
{
public:
    // Use Builder to instantiate objects
    class Builder : public IObjA::Builder
    {
        // hide evil auto created assignment operator, no implementation
                void          operator=(const Builder& );
        // hide default constructor for abstract object, no implementation
                              Builder  ();
    public:
        // Destructor of Builder
        /*lax*/               ~Builder ();

        // Instantiates IObjA2 instance with the current initialization of
        // the fields. After the instance is ready the builder could be
        // reused to instantiate more objects. The data is not reset.
        // Second call of build() will instantiate object with the same
        // data.
                const IObjA2& build    ()                    const;

        // Provides the internal instantiated builder object and
        // invalidates the builder status. Once finalize() is called, the
        // builder can not be used again. Use finalize() when you no longer
        // are going to use this builder.
                IObjA2SPtr    finalize ();


        // Setter method for the data field o
                Builder&      set_o    (long o);

        // Setter method for the data field inner
                Builder&      set_inner(const EInner& inner);

        // Setter method for the data field a
                Builder&      set_a    (long a);

        // Setter method for the data field a2
                Builder&      set_a2   (long a2);

    protected:
        // constructor needed from potential derived classes
                              Builder  (IObjA2RPtr pObject);
    };

    // Default constructor
                       IObjA2         ();
    // Destructor
    virtual            ~IObjA2        ();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  IObjA2SPtr downcast       (const IObjSPtr& object);

    // Identifier for the objects from IObjA2 class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EIObjId    staticIObjId   ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EIObjId    runtimeIObjId  ()                       const;

    // Inproc identifier for the objects from IObjA2 class.
    // Note: this identificator is unique just for the process session.
    // There is no guarantee that the id will be the same from session to
    // session. Do not use for serialization.
    static  size_t     staticInprocId ();
    // This virtual method provides runtime inproc object identification
    // based on the polymorphic behavior of the virtual methods. Allows
    // having a RTTI like mechanism significantly cheaper than the RTTI
    // provided by the compilers themselves.
    virtual size_t     runtimeInprocId()                       const;

    // Getter method for the data field a2
            long       a2             ()                       const;

private:
    // variable for the data field a2
    long mA2;
};

// IObjB is an immutable class - once instantiated none of the data fields
// can be changed. For the initial initialization and instantiation use the
// nested Builder class.

// Immutability is useful in multi-thread and subject observer
// applications. It makes easy creation of models with object references.

class IObjB : public IObj
{
public:
    // Use Builder to instantiate objects
    class Builder : public IObj::Builder
    {
        // hide evil auto created assignment operator, no implementation
                void         operator=(const Builder& );
    public:
        // Default constructor. All fields without default values are left
        // uninitialized. Make sure you initialize all the necessary fields
        // before instantiating
                             Builder  ();
        // Use this constructor when you need to clone or create an object
        // just slightly different from another object
                             Builder  (const IObjB& object);
        // Destructor of Builder
        /*lax*/              ~Builder ();

        // Instantiates IObjB instance with the current initialization of
        // the fields. After the instance is ready the builder could be
        // reused to instantiate more objects. The data is not reset.
        // Second call of build() will instantiate object with the same
        // data.
                const IObjB& build    ()                    const;

        // Provides the internal instantiated builder object and
        // invalidates the builder status. Once finalize() is called, the
        // builder can not be used again. Use finalize() when you no longer
        // are going to use this builder.
                IObjBSPtr    finalize ();


        // Setter method for the data field o
                Builder&     set_o    (long o);

        // Setter method for the data field inner
                Builder&     set_inner(const EInner& inner);

        // Setter method for the data field b
                Builder&     set_b    (long b);

    protected:
        // constructor needed from potential derived classes
                             Builder  (IObjBRPtr pObject);
    };

    // Default constructor
                      IObjB   ();
    // Destructor
    virtual           ~IObjB  ();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  IObjBSPtr downcast(const IObjSPtr& object);

    // Getter method for the data field b
            long      b       ()                       const;

private:
    // variable for the data field b
    long mB;
};

// IObjB1 is an immutable class - once instantiated none of the data fields
// can be changed. For the initial initialization and instantiation use the
// nested Builder class.

// Immutability is useful in multi-thread and subject observer
// applications. It makes easy creation of models with object references.

class IObjB1 : public IObjB
{
public:
    // Use Builder to instantiate objects
    class Builder : public IObjB::Builder
    {
        // hide evil auto created assignment operator, no implementation
                void          operator=(const Builder& );
    public:
        // Default constructor. All fields without default values are left
        // uninitialized. Make sure you initialize all the necessary fields
        // before instantiating
                              Builder  ();
        // Use this constructor when you need to clone or create an object
        // just slightly different from another object
                              Builder  (const IObjB1& object);
        // Destructor of Builder
        /*lax*/               ~Builder ();

        // Instantiates IObjB1 instance with the current initialization of
        // the fields. After the instance is ready the builder could be
        // reused to instantiate more objects. The data is not reset.
        // Second call of build() will instantiate object with the same
        // data.
                const IObjB1& build    ()                     const;

        // Provides the internal instantiated builder object and
        // invalidates the builder status. Once finalize() is called, the
        // builder can not be used again. Use finalize() when you no longer
        // are going to use this builder.
                IObjB1SPtr    finalize ();


        // Setter method for the data field o
                Builder&      set_o    (long o);

        // Setter method for the data field inner
                Builder&      set_inner(const EInner& inner);

        // Setter method for the data field b
                Builder&      set_b    (long b);

        // Setter method for the data field b1
                Builder&      set_b1   (long b1);

    protected:
        // constructor needed from potential derived classes
                              Builder  (IObjB1RPtr pObject);
    };

    // Default constructor
                       IObjB1       ();
    // Destructor
    virtual            ~IObjB1      ();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  IObjB1SPtr downcast     (const IObjSPtr& object);

    // Identifier for the objects from IObjB1 class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EIObjId    staticIObjId ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EIObjId    runtimeIObjId()                       const;

    // Getter method for the data field b1
            long       b1           ()                       const;

private:
    // variable for the data field b1
    long mB1;
};

// This enumeration class provides namespaced set of constant values.
// It is designed to provide type control over operations with enum values
// without need to wait all compilers you are going to use for this project
// to support C++0x standard. The type control do not prevent the variables
// to be used in switch statements.
class EIObjId
{
public:
    // Default constructor - sets the value to invalid
                         EIObjId   ();
    // Constructor from an integer value.
    // Note: Avoid using this constructor if possible. It is appropriate
    // only in case of importing value from components that you do not have
    // control over (such as 3rd party libraries or serialization
    // functionality).
    explicit             EIObjId   (long value);

    // Returns the integer value of the enum.
    // Note: Avoid using this method if possible. It is appropriate only in
    // case of exporting value to components that you do not have control
    // over (such as 3rd party libraries or serialization functionality).
             long        value     ()                      const;
    // Returns short name for a specified enum value
    static   const char* shortName (long value);
    // Returns short name of the enum value
             const char* shortName ()                      const;
    // returns true if the value of the enum is equal to the value of the
    // argument
             bool        operator==(const EIObjId& rValue) const;
    // returns true if the value of the enum is not equal to the value of
    // the argument
             bool        operator!=(const EIObjId& rValue) const;

    // static methods for enum class objects
    static const EIObjId invalid();
    static const EIObjId iObj   ();
    static const EIObjId iObjA  ();
    static const EIObjId iObjA2 ();
    static const EIObjId iObjB1 ();

    // This enum provides static constants that could be used in a switch
    // statements
    enum
    {
        kInvalid = 0,
        kIObj    = 1,
        kIObjA   = 2,
        kIObjA2  = 3,
        kIObjB1  = 4,
    };

private:
    // Member variable that holds the enum value
    long mValue;
};

class HierarchyIObjFactory
{
public:
    static IObjSPtr   clone         (const IObjSPtr& object);
    static IObjASPtr  downcastIObjA (const IObjSPtr& object);
    static IObjA2SPtr downcastIObjA2(const IObjSPtr& object);
    static IObjB1SPtr downcastIObjB1(const IObjSPtr& object);
};

class MOObj
{
public:
    // Default constructor
                   MOObj ();
    // Destructor
    /*lax*/        ~MOObj();

    // Getter method for the data field i
            long   i     ()       const;
    // Setter method for the data field i
            MOObj& set_i (long i);

    // Getter method for the data field o
            long   o     ()       const;
    // Setter method for the data field o
            MOObj& set_o (long o);

    // This enumeration class provides namespaced set of constant values.
    class EWeak
    {
    public:
        // Default constructor - sets the value to invalid
                             EWeak    ( );
        // Constructor from an integer value.
                             EWeak    ( long value);

        // Returns the integer value of the enum.
               long          value    ( )           const;
        // Returns short name for a specified enum value
        static const char*   shortName( long value);
        // Returns short name of the enum value
               const char*   shortName( )           const;
        // Cast operator that casts the enum to its native type
               operator long (        ) const;

        // static methods for enum class objects
        static const long invalid();
        static const long value1 ();
        static const long value2 ();

        // This enum provides static constants that could be used in a
        // switch statements
        enum
        {
            kInvalid = 0,
            kValue1  = 1,
            kValue2  = 2,
        };

    private:
        // Member variable that holds the enum value
        long mValue;
    };

    // This enumeration class provides namespaced set of constant values.
    // It is designed to provide type control over operations with enum
    // values without need to wait all compilers you are going to use for
    // this project to support C++0x standard. The type control do not
    // prevent the variables to be used in switch statements.
    class EStrong
    {
    public:
        // Default constructor - sets the value to invalid
                             EStrong   ();
        // Constructor from an integer value.
        // Note: Avoid using this constructor if possible. It is
        // appropriate only in case of importing value from components that
        // you do not have control over (such as 3rd party libraries or
        // serialization functionality).
        explicit             EStrong   (long value);

        // Returns the integer value of the enum.
        // Note: Avoid using this method if possible. It is appropriate
        // only in case of exporting value to components that you do not
        // have control over (such as 3rd party libraries or serialization
        // functionality).
                 long        value     ()                      const;
        // Returns short name for a specified enum value
        static   const char* shortName (long value);
        // Returns short name of the enum value
                 const char* shortName ()                      const;
        // returns true if the value of the enum is equal to the value of
        // the argument
                 bool        operator==(const EStrong& rValue) const;
        // returns true if the value of the enum is not equal to the value
        // of the argument
                 bool        operator!=(const EStrong& rValue) const;

        // static methods for enum class objects
        static const EStrong invalid();
        static const EStrong value1 ();
        static const EStrong value2 ();

        // This enum provides static constants that could be used in a
        // switch statements
        enum
        {
            kInvalid = 0,
            kValue1  = 1,
            kValue2  = 2,
        };

    private:
        // Member variable that holds the enum value
        long mValue;
    };

    // Getter method for the data field w
    const EWeak&   w        ()                 const;
    // Setter method for the data field w
    MOObj&         set_w    (const EWeak& w);
    // Provides mutable access to field w
    EWeak&         mutable_w();

    // Getter method for the data field s
    const EStrong& s        ()                 const;
    // Setter method for the data field s
    MOObj&         set_s    (const EStrong& s);
    // Provides mutable access to field s
    EStrong&       mutable_s();

private:
    // variable for the data field i
    long    mI;
    // variable for the data field o
    long    mO;
    // variable for the data field w
    EWeak   mW;
    // variable for the data field s
    EStrong mS;
};

class MObjectObjFactory
{
public:
    static MOObjSPtr create(long i, const MOObj::EWeak& w, const MOObj::EStrong& s);
    static MOObjSPtr create(long i, long o, const MOObj::EWeak& w, const MOObj::EStrong& s);
};

MOObjSPtr CreateMObjectObj(long i, const MOObj::EWeak& w, const MOObj::EStrong& s);
MOObjSPtr CreateMObjectObj(long i, long o, const MOObj::EWeak& w, const MOObj::EStrong& s);

// IMOObj is an immutable class - once instantiated none of the data fields
// can be changed. For the initial initialization and instantiation use the
// nested Builder class.

// Immutability is useful in multi-thread and subject observer
// applications. It makes easy creation of models with object references.

class IMOObj
{
public:
    // Use Builder to instantiate objects
    class Builder
    {
        // hide evil auto created assignment operator, no implementation
                void          operator=(const Builder& );
    public:
        // Default constructor. All fields without default values are left
        // uninitialized. Make sure you initialize all the necessary fields
        // before instantiating
                              Builder  ();
        // Use this constructor when you need to clone or create an object
        // just slightly different from another object
                              Builder  (const IMOObj& object);
        // Destructor of Builder
        /*lax*/               ~Builder ();

        // Instantiates IMOObj instance with the current initialization of
        // the fields. After the instance is ready the builder could be
        // reused to instantiate more objects. The data is not reset.
        // Second call of build() will instantiate object with the same
        // data.
                const IMOObj& build    ()                     const;

        // Provides the internal instantiated builder object and
        // invalidates the builder status. Once finalize() is called, the
        // builder can not be used again. Use finalize() when you no longer
        // are going to use this builder.
                IMOObjSPtr    finalize ();


        // Setter method for the data field i
                Builder&      set_i    (unsigned char i);

        // Setter method for the data field o
                Builder&      set_o    (unsigned short o);

    protected:
        // constructor needed from potential derived classes
                              Builder  (IMOObjRPtr pObject);

        IMOObjRPtr mpObject;
    };

    // Default constructor
                           IMOObj ();
    // Destructor
    /*lax*/                ~IMOObj();

    // Getter method for the data field i
            unsigned char  i      () const;

    // Getter method for the data field o
            unsigned short o      () const;

private:
    // variable for the data field i
    unsigned char  mI;
    // variable for the data field o
    unsigned short mO;
};

class IMObjectObjFactory
{
public:
    static IMOObjSPtr create(unsigned char i);
    static IMOObjSPtr create(unsigned char i, unsigned short o);
};

// IMOObj2 is an immutable class - once instantiated none of the data
// fields can be changed. For the initial initialization and instantiation
// use the nested Builder class.

// Immutability is useful in multi-thread and subject observer
// applications. It makes easy creation of models with object references.

class IMOObj2 : public IMOObj
{
public:
    // Use Builder to instantiate objects
    class Builder : public IMOObj::Builder
    {
        // hide evil auto created assignment operator, no implementation
                void           operator=(const Builder& );
    public:
        // Default constructor. All fields without default values are left
        // uninitialized. Make sure you initialize all the necessary fields
        // before instantiating
                               Builder  ();
        // Use this constructor when you need to clone or create an object
        // just slightly different from another object
                               Builder  (const IMOObj2& object);
        // Destructor of Builder
        /*lax*/                ~Builder ();

        // Instantiates IMOObj2 instance with the current initialization of
        // the fields. After the instance is ready the builder could be
        // reused to instantiate more objects. The data is not reset.
        // Second call of build() will instantiate object with the same
        // data.
                const IMOObj2& build    ()                      const;

        // Provides the internal instantiated builder object and
        // invalidates the builder status. Once finalize() is called, the
        // builder can not be used again. Use finalize() when you no longer
        // are going to use this builder.
                IMOObj2SPtr    finalize ();


        // Setter method for the data field i
                Builder&       set_i    (unsigned char i);

        // Setter method for the data field o
                Builder&       set_o    (unsigned short o);

        // Setter method for the data field i2
                Builder&       set_i2   (unsigned long i2);

        // Setter method for the data field o2
                Builder&       set_o2   (unsigned long long o2);

    protected:
        // constructor needed from potential derived classes
                               Builder  (IMOObj2RPtr pObject);
    };

    // Default constructor
                               IMOObj2 ();
    // Destructor
    /*lax*/                    ~IMOObj2();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  IMOObj2SPtr        downcast(const IMOObjSPtr& object);

    // Getter method for the data field i2
            unsigned long      i2      ()                         const;

    // Getter method for the data field o2
            unsigned long long o2      ()                         const;

private:
    // variable for the data field i2
    unsigned long      mI2;
    // variable for the data field o2
    unsigned long long mO2;
};

class IMObjectObj2Factory
{
public:
    static IMOObj2SPtr create(unsigned char i, unsigned long i2);
    static IMOObj2SPtr create(unsigned char i, unsigned short o, unsigned long i2);
    static IMOObj2SPtr create(unsigned char i, unsigned long i2, unsigned long long o2);
    static IMOObj2SPtr create(unsigned char i, unsigned short o, unsigned long i2, unsigned long long o2);
};

}

#else // __GENERATOR_TEST_FACTORIES_COMPIL_H_

namespace factories
{

// Forward declarations
class ObjBase;
typedef ObjBase*                         ObjBaseRPtr;
typedef boost::shared_ptr<ObjBase>       ObjBaseSPtr;
typedef boost::shared_ptr<const ObjBase> ObjBaseSCPtr;
typedef boost::weak_ptr<ObjBase>         ObjBaseWPtr;

class IObjBase;
typedef IObjBase*                         IObjBaseRPtr;
typedef boost::shared_ptr<IObjBase>       IObjBaseSPtr;
typedef boost::shared_ptr<const IObjBase> IObjBaseSCPtr;
typedef boost::weak_ptr<IObjBase>         IObjBaseWPtr;

class Obj;
typedef Obj*                         ObjRPtr;
typedef boost::shared_ptr<Obj>       ObjSPtr;
typedef boost::shared_ptr<const Obj> ObjSCPtr;
typedef boost::weak_ptr<Obj>         ObjWPtr;

class EObjId;

class PluginObjFactory;
typedef PluginObjFactory*                         PluginObjFactoryRPtr;
typedef boost::shared_ptr<PluginObjFactory>       PluginObjFactorySPtr;
typedef boost::shared_ptr<const PluginObjFactory> PluginObjFactorySCPtr;
typedef boost::weak_ptr<PluginObjFactory>         PluginObjFactoryWPtr;

class ObjA;
typedef ObjA*                         ObjARPtr;
typedef boost::shared_ptr<ObjA>       ObjASPtr;
typedef boost::shared_ptr<const ObjA> ObjASCPtr;
typedef boost::weak_ptr<ObjA>         ObjAWPtr;

class EObjId;

class ObjA1;
typedef ObjA1*                         ObjA1RPtr;
typedef boost::shared_ptr<ObjA1>       ObjA1SPtr;
typedef boost::shared_ptr<const ObjA1> ObjA1SCPtr;
typedef boost::weak_ptr<ObjA1>         ObjA1WPtr;

class ObjA2;
typedef ObjA2*                         ObjA2RPtr;
typedef boost::shared_ptr<ObjA2>       ObjA2SPtr;
typedef boost::shared_ptr<const ObjA2> ObjA2SCPtr;
typedef boost::weak_ptr<ObjA2>         ObjA2WPtr;

class EObjId;

class ObjB;
typedef ObjB*                         ObjBRPtr;
typedef boost::shared_ptr<ObjB>       ObjBSPtr;
typedef boost::shared_ptr<const ObjB> ObjBSCPtr;
typedef boost::weak_ptr<ObjB>         ObjBWPtr;

class ObjB1;
typedef ObjB1*                         ObjB1RPtr;
typedef boost::shared_ptr<ObjB1>       ObjB1SPtr;
typedef boost::shared_ptr<const ObjB1> ObjB1SCPtr;
typedef boost::weak_ptr<ObjB1>         ObjB1WPtr;

class EObjId;

class HierarchyObjFactory;
typedef HierarchyObjFactory*                         HierarchyObjFactoryRPtr;
typedef boost::shared_ptr<HierarchyObjFactory>       HierarchyObjFactorySPtr;
typedef boost::shared_ptr<const HierarchyObjFactory> HierarchyObjFactorySCPtr;
typedef boost::weak_ptr<HierarchyObjFactory>         HierarchyObjFactoryWPtr;

class EObjId;
typedef EObjId*                         ObjIdRPtr;
typedef boost::shared_ptr<EObjId>       ObjIdSPtr;
typedef boost::shared_ptr<const EObjId> ObjIdSCPtr;
typedef boost::weak_ptr<EObjId>         ObjIdWPtr;

class HierarchyObjFactory;

class IObj;
typedef IObj*                         IObjRPtr;
typedef boost::shared_ptr<IObj>       IObjSPtr;
typedef boost::shared_ptr<const IObj> IObjSCPtr;
typedef boost::weak_ptr<IObj>         IObjWPtr;

class EIObjId;

class IPluginObjFactory;
typedef IPluginObjFactory*                         IPluginObjFactoryRPtr;
typedef boost::shared_ptr<IPluginObjFactory>       IPluginObjFactorySPtr;
typedef boost::shared_ptr<const IPluginObjFactory> IPluginObjFactorySCPtr;
typedef boost::weak_ptr<IPluginObjFactory>         IPluginObjFactoryWPtr;

class IObjA;
typedef IObjA*                         IObjARPtr;
typedef boost::shared_ptr<IObjA>       IObjASPtr;
typedef boost::shared_ptr<const IObjA> IObjASCPtr;
typedef boost::weak_ptr<IObjA>         IObjAWPtr;

class EIObjId;

class IObjA1;
typedef IObjA1*                         IObjA1RPtr;
typedef boost::shared_ptr<IObjA1>       IObjA1SPtr;
typedef boost::shared_ptr<const IObjA1> IObjA1SCPtr;
typedef boost::weak_ptr<IObjA1>         IObjA1WPtr;

class IObjA2;
typedef IObjA2*                         IObjA2RPtr;
typedef boost::shared_ptr<IObjA2>       IObjA2SPtr;
typedef boost::shared_ptr<const IObjA2> IObjA2SCPtr;
typedef boost::weak_ptr<IObjA2>         IObjA2WPtr;

class EIObjId;

class IObjB;
typedef IObjB*                         IObjBRPtr;
typedef boost::shared_ptr<IObjB>       IObjBSPtr;
typedef boost::shared_ptr<const IObjB> IObjBSCPtr;
typedef boost::weak_ptr<IObjB>         IObjBWPtr;

class IObjB1;
typedef IObjB1*                         IObjB1RPtr;
typedef boost::shared_ptr<IObjB1>       IObjB1SPtr;
typedef boost::shared_ptr<const IObjB1> IObjB1SCPtr;
typedef boost::weak_ptr<IObjB1>         IObjB1WPtr;

class EIObjId;

class HierarchyIObjFactory;
typedef HierarchyIObjFactory*                         HierarchyIObjFactoryRPtr;
typedef boost::shared_ptr<HierarchyIObjFactory>       HierarchyIObjFactorySPtr;
typedef boost::shared_ptr<const HierarchyIObjFactory> HierarchyIObjFactorySCPtr;
typedef boost::weak_ptr<HierarchyIObjFactory>         HierarchyIObjFactoryWPtr;

class EIObjId;
typedef EIObjId*                         IObjIdRPtr;
typedef boost::shared_ptr<EIObjId>       IObjIdSPtr;
typedef boost::shared_ptr<const EIObjId> IObjIdSCPtr;
typedef boost::weak_ptr<EIObjId>         IObjIdWPtr;

class HierarchyIObjFactory;

class MOObj;
typedef MOObj*                         MOObjRPtr;
typedef boost::shared_ptr<MOObj>       MOObjSPtr;
typedef boost::shared_ptr<const MOObj> MOObjSCPtr;
typedef boost::weak_ptr<MOObj>         MOObjWPtr;

class MObjectObjFactory;

class IMOObj;
typedef IMOObj*                         IMOObjRPtr;
typedef boost::shared_ptr<IMOObj>       IMOObjSPtr;
typedef boost::shared_ptr<const IMOObj> IMOObjSCPtr;
typedef boost::weak_ptr<IMOObj>         IMOObjWPtr;

class IMObjectObjFactory;

class IMOObj2;
typedef IMOObj2*                         IMOObj2RPtr;
typedef boost::shared_ptr<IMOObj2>       IMOObj2SPtr;
typedef boost::shared_ptr<const IMOObj2> IMOObj2SCPtr;
typedef boost::weak_ptr<IMOObj2>         IMOObj2WPtr;

class IMObjectObj2Factory;

}

#endif // __GENERATOR_TEST_FACTORIES_COMPIL_H_

