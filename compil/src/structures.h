// Boost C++ Smart Pointers
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#ifndef __GENERATOR_TEST_STRUCTURES_COMPIL_H_
#define __GENERATOR_TEST_STRUCTURES_COMPIL_H_

#include "structures.h"
// Boost C++ Smart Pointers
#include <boost/enable_shared_from_this.hpp>

class StructureIsInitialize : public boost::enable_shared_from_this<StructureIsInitialize>
{
public:
    // Default constructor
                                   StructureIsInitialize ();
    // Destructor
    /*lax*/                        ~StructureIsInitialize();

    // Returns true if every required field is initialized.
            bool                   isInitialized         ()       const;

    // Getter method for the data field r
            long                   r                     ()       const;
    // Returns true if the data field r was set and could be considered
    // valid
            bool                   valid_r               ()       const;
    // Setter method for the data field r
            StructureIsInitialize& set_r                 (long r);
    // Erases the required data field r. Object can not be instantiated
    // before the field data is set again
            void                   erase_r               ();

    // Getter method for the data field o
            long                   o                     ()       const;
    // Checks if the optional field o exists
            bool                   exist_o               ()       const;
    // Setter method for the data field o
            StructureIsInitialize& set_o                 (long o);
    // Clears the optional data field o
            void                   clear_o               ();

    // Getter method for the data field d
            long                   d                     ()       const;
    // Returns true if the data field value d was changed from its default
    // value 1
            bool                   changed_d             ()       const;
    // Returns the default value 1 of the field d
    static  long                   default_d             ();
    // Setter method for the data field d
            StructureIsInitialize& set_d                 (long d);
    // Updates the data field d. If the new value is equal to the default
    // it clears the field else it sets it to the new value
            StructureIsInitialize& update_d              (long d);
    // Resets the data field d to its default value 1
            void                   reset_d               ();

private:
    // Returns unique bitmask value for the field r
    static int bitmask_r();
    // Returns unique bitmask value for the field o
    static int bitmask_o();
    // Returns unique bitmask value for the field d
    static int bitmask_d();

    // Stores availability information for the fields
    int  mBits;

    // variable for the data field r
    long mR;
    // variable for the data field o
    long mO;
    // variable for the data field d
    long mD;
};

class StructureIsInitialize1 : public StructureIsInitialize
{
public:
    // Default constructor
                                       StructureIsInitialize1 ();
    // Destructor
    /*lax*/                            ~StructureIsInitialize1();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  StructureIsInitialize1SPtr downcast               (const StructureIsInitializeSPtr& object);

    // Returns the alter value 5 of the field r
    static  long                       alter_r                ();
};

class StructureIsInitialize2 : public StructureIsInitialize
{
public:
    // Default constructor
                                       StructureIsInitialize2 ();
    // Destructor
    /*lax*/                            ~StructureIsInitialize2();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  StructureIsInitialize2SPtr downcast               (const StructureIsInitializeSPtr& object);

    // Returns true if every required field is initialized.
            bool                       isInitialized          ()                                        const;

    // Getter method for the data field r2
            long                       r2                     ()                                        const;
    // Returns true if the data field r2 was set and could be considered
    // valid
            bool                       valid_r2               ()                                        const;
    // Setter method for the data field r2
            StructureIsInitialize2&    set_r2                 (long r2);
    // Erases the required data field r2. Object can not be instantiated
    // before the field data is set again
            void                       erase_r2               ();

private:
    // Returns unique bitmask value for the field r2
    static int bitmask_r2();

    // Stores availability information for the fields
    int  mBits;

    // variable for the data field r2
    long mR2;
};

class StructureNonControlledInherit : public StructureIsInitialize
{
public:
    // Default constructor
                                               StructureNonControlledInherit ();
    // Destructor
    /*lax*/                                    ~StructureNonControlledInherit();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  StructureNonControlledInheritSPtr  downcast                      (const StructureIsInitializeSPtr& object);
    // shared_from_this is a helper method that overrides the
    // shared_from_this method that is implemented in
    // boost::enable_shared_from_this base class. The only purpose of this
    // helper method is to eliminate the need of downcasting to shared_ptr
    // to this class.
            StructureNonControlledInheritSPtr  shared_from_this              ();
    // This method is exactly the same as the previous one with exception
    // that it allows shared_from_this to be called from const methods.
            StructureNonControlledInheritSCPtr shared_from_this              ()                                        const;
};

class StructureIsInitialize3 : public StructureNonControlledInherit
{
public:
    // Default constructor
                                        StructureIsInitialize3 ();
    // Destructor
    /*lax*/                             ~StructureIsInitialize3();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  StructureIsInitialize3SPtr  downcast               (const StructureIsInitializeSPtr& object);
    // shared_from_this is a helper method that overrides the
    // shared_from_this method that is implemented in
    // boost::enable_shared_from_this base class. The only purpose of this
    // helper method is to eliminate the need of downcasting to shared_ptr
    // to this class.
            StructureIsInitialize3SPtr  shared_from_this       ();
    // This method is exactly the same as the previous one with exception
    // that it allows shared_from_this to be called from const methods.
            StructureIsInitialize3SCPtr shared_from_this       ()                                        const;

    // Returns true if every required field is initialized.
            bool                        isInitialized          ()                                        const;

    // Getter method for the data field r3
            long                        r3                     ()                                        const;
    // Returns true if the data field r3 was set and could be considered
    // valid
            bool                        valid_r3               ()                                        const;
    // Setter method for the data field r3
            StructureIsInitialize3&     set_r3                 (long r3);
    // Erases the required data field r3. Object can not be instantiated
    // before the field data is set again
            void                        erase_r3               ();

private:
    // Returns unique bitmask value for the field r3
    static int bitmask_r3();

    // Stores availability information for the fields
    int  mBits;

    // variable for the data field r3
    long mR3;
};

class StructureNonControlled : public StructureIsInitialize
{
public:
    // Default constructor
                                       StructureNonControlled ();
    // Destructor
    /*lax*/                            ~StructureNonControlled();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  StructureNonControlledSPtr downcast               (const StructureIsInitializeSPtr& object);
};

class StructureIsInitialize4 : public StructureNonControlled
{
public:
    // Default constructor
                                       StructureIsInitialize4 ();
    // Destructor
    /*lax*/                            ~StructureIsInitialize4();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  StructureIsInitialize4SPtr downcast               (const StructureIsInitializeSPtr& object);

    // Returns true if every required field is initialized.
            bool                       isInitialized          ()                                        const;

    // Getter method for the data field r4
            long                       r4                     ()                                        const;
    // Returns true if the data field r4 was set and could be considered
    // valid
            bool                       valid_r4               ()                                        const;
    // Setter method for the data field r4
            StructureIsInitialize4&    set_r4                 (long r4);
    // Erases the required data field r4. Object can not be instantiated
    // before the field data is set again
            void                       erase_r4               ();

private:
    // Returns unique bitmask value for the field r4
    static int bitmask_r4();

    // Stores availability information for the fields
    int  mBits;

    // variable for the data field r4
    long mR4;
};

class StructureIsInitializeVirtual
{
public:
    // Default constructor
                                            StructureIsInitializeVirtual         ();
    // Destructor
    virtual                                 ~StructureIsInitializeVirtual        ();

    // Returns true if every required field is initialized.
    virtual bool                            isInitialized                        ()       const;

    // Identifier for the objects from StructureIsInitializeVirtual class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EStructureIsInitializeVirtualId staticStructureIsInitializeVirtualId ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EStructureIsInitializeVirtualId runtimeStructureIsInitializeVirtualId()       const;

    // Getter method for the data field r
            long                            r                                    ()       const;
    // Returns true if the data field r was set and could be considered
    // valid
            bool                            valid_r                              ()       const;
    // Setter method for the data field r
            StructureIsInitializeVirtual&   set_r                                (long r);
    // Erases the required data field r. Object can not be instantiated
    // before the field data is set again
            void                            erase_r                              ();

private:
    // Returns unique bitmask value for the field r
    static int bitmask_r();

    // Stores availability information for the fields
    int  mBits;

    // variable for the data field r
    long mR;
};

class StructureNonControlledVirtualInherit : public StructureIsInitializeVirtual
{
public:
    // Default constructor
                                                     StructureNonControlledVirtualInherit ();
    // Destructor
    virtual                                          ~StructureNonControlledVirtualInherit();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  StructureNonControlledVirtualInheritSPtr downcast                             (const StructureIsInitializeVirtualSPtr& object);
};

class StructureIsInitialize5 : public StructureNonControlledVirtualInherit
{
public:
    // Default constructor
                                       StructureIsInitialize5 ();
    // Destructor
    virtual                            ~StructureIsInitialize5();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  StructureIsInitialize5SPtr downcast               (const StructureIsInitializeVirtualSPtr& object);

    // Returns true if every required field is initialized.
    virtual bool                       isInitialized          ()                                               const;

    // Getter method for the data field r5
            long                       r5                     ()                                               const;
    // Returns true if the data field r5 was set and could be considered
    // valid
            bool                       valid_r5               ()                                               const;
    // Setter method for the data field r5
            StructureIsInitialize5&    set_r5                 (long r5);
    // Erases the required data field r5. Object can not be instantiated
    // before the field data is set again
            void                       erase_r5               ();

private:
    // Returns unique bitmask value for the field r5
    static int bitmask_r5();

    // Stores availability information for the fields
    int  mBits;

    // variable for the data field r5
    long mR5;
};

class StructureNonControlledVirtual
{
public:
    // Default constructor
                                             StructureNonControlledVirtual         ();
    // Destructor
    virtual                                  ~StructureNonControlledVirtual        ();

    // Identifier for the objects from StructureNonControlledVirtual class.
    // Note: it is not defined in the respective cpp file. Instead it is
    // defined in the factory class together with all the other identifiers
    // of the other class objects. This allows all identifiers to be
    // maintained from a single place, which reduces the risk of value
    // collisions
    static  EStructureNonControlledVirtualId staticStructureNonControlledVirtualId ();
    // This virtual method provides runtime object identification based on
    // the polymorphic behavior of the virtual methods. Allows having a
    // RTTI like mechanism significantly cheaper than the RTTI provided by
    // the compilers themselves.
    virtual EStructureNonControlledVirtualId runtimeStructureNonControlledVirtualId()       const;

    // Getter method for the data field r
            long                             r                                     ()       const;
    // Setter method for the data field r
            StructureNonControlledVirtual&   set_r                                 (long r);

private:
    // variable for the data field r
    long mR;
};

class StructureIsInitialize6 : public StructureNonControlledVirtual
{
public:
    // Default constructor
                                       StructureIsInitialize6 ();
    // Destructor
    virtual                            ~StructureIsInitialize6();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  StructureIsInitialize6SPtr downcast               (const StructureNonControlledVirtualSPtr& object);

    // Returns true if every required field is initialized.
    virtual bool                       isInitialized          ()                                                const;

    // Getter method for the data field r6
            long                       r6                     ()                                                const;
    // Returns true if the data field r6 was set and could be considered
    // valid
            bool                       valid_r6               ()                                                const;
    // Setter method for the data field r6
            StructureIsInitialize6&    set_r6                 (long r6);
    // Erases the required data field r6. Object can not be instantiated
    // before the field data is set again
            void                       erase_r6               ();

private:
    // Returns unique bitmask value for the field r6
    static int bitmask_r6();

    // Stores availability information for the fields
    int  mBits;

    // variable for the data field r6
    long mR6;
};

class StructureIsVoid
{
public:
    // Default constructor
                             StructureIsVoid ();
    // Destructor
    /*lax*/                  ~StructureIsVoid();

    // Returns true if every required field is initialized.
            bool             isInitialized   ()       const;

            bool             isVoid          ()       const;

    // Getter method for the data field o
            long             o               ()       const;
    // Checks if the optional field o exists
            bool             exist_o         ()       const;
    // Setter method for the data field o
            StructureIsVoid& set_o           (long o);
    // Clears the optional data field o
            void             clear_o         ();

private:
    // Returns unique bitmask value for the field o
    static int bitmask_o();

    // Stores availability information for the fields
    int  mBits;

    // variable for the data field o
    long mO;
};

class StructureIsVoid1 : public StructureIsVoid
{
public:
    // Default constructor
                                 StructureIsVoid1 ();
    // Destructor
    /*lax*/                      ~StructureIsVoid1();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  StructureIsVoid1SPtr downcast         (const StructureIsVoidSPtr& object);

    // Returns true if every required field is initialized.
            bool                 isInitialized    ()                                  const;

            bool                 isVoid           ()                                  const;

    // Getter method for the data field o1
            long                 o1               ()                                  const;
    // Checks if the optional field o1 exists
            bool                 exist_o1         ()                                  const;
    // Setter method for the data field o1
            StructureIsVoid1&    set_o1           (long o1);
    // Clears the optional data field o1
            void                 clear_o1         ();

private:
    // Returns unique bitmask value for the field o1
    static int bitmask_o1();

    // Stores availability information for the fields
    int  mBits;

    // variable for the data field o1
    long mO1;
};

// This enumeration class provides namespaced set of constant values.
// It is designed to provide type control over operations with enum values
// without need to wait all compilers you are going to use for this project
// to support C++0x standard. The type control do not prevent the variables
// to be used in switch statements.
class EStructureIsInitializeVirtualId
{
public:
    // Default constructor - sets the value to invalid
                         EStructureIsInitializeVirtualId();
    // Constructor from an integer value.
    // Note: Avoid using this constructor if possible. It is appropriate
    // only in case of importing value from components that you do not have
    // control over (such as 3rd party libraries or serialization
    // functionality).
    explicit             EStructureIsInitializeVirtualId(long value);

    // Returns the integer value of the enum.
    // Note: Avoid using this method if possible. It is appropriate only in
    // case of exporting value to components that you do not have control
    // over (such as 3rd party libraries or serialization functionality).
             long        value                          ()                                              const;
    // Returns short name for a specified enum value
    static   const char* shortName                      (long value);
    // Returns short name of the enum value
             const char* shortName                      ()                                              const;
    // returns true if the value of the enum is equal to the value of the
    // argument
             bool        operator==                     (const EStructureIsInitializeVirtualId& rValue) const;
    // returns true if the value of the enum is not equal to the value of
    // the argument
             bool        operator!=                     (const EStructureIsInitializeVirtualId& rValue) const;

    // static methods for enum class objects
    static const EStructureIsInitializeVirtualId invalid                     ();
    static const EStructureIsInitializeVirtualId structureIsInitializeVirtual();

    // This enum provides static constants that could be used in a switch
    // statements
    enum
    {
        kInvalid                      = 0,
        kStructureIsInitializeVirtual = 1,
    };

private:
    // Member variable that holds the enum value
    long mValue;
};

class StructureIsInitializeVirtualFactory
{
public:
    static StructureIsInitializeVirtualSPtr clone(const StructureIsInitializeVirtualSPtr& object);
};

// This enumeration class provides namespaced set of constant values.
// It is designed to provide type control over operations with enum values
// without need to wait all compilers you are going to use for this project
// to support C++0x standard. The type control do not prevent the variables
// to be used in switch statements.
class EStructureNonControlledVirtualId
{
public:
    // Default constructor - sets the value to invalid
                         EStructureNonControlledVirtualId();
    // Constructor from an integer value.
    // Note: Avoid using this constructor if possible. It is appropriate
    // only in case of importing value from components that you do not have
    // control over (such as 3rd party libraries or serialization
    // functionality).
    explicit             EStructureNonControlledVirtualId(long value);

    // Returns the integer value of the enum.
    // Note: Avoid using this method if possible. It is appropriate only in
    // case of exporting value to components that you do not have control
    // over (such as 3rd party libraries or serialization functionality).
             long        value                           ()                                               const;
    // Returns short name for a specified enum value
    static   const char* shortName                       (long value);
    // Returns short name of the enum value
             const char* shortName                       ()                                               const;
    // returns true if the value of the enum is equal to the value of the
    // argument
             bool        operator==                      (const EStructureNonControlledVirtualId& rValue) const;
    // returns true if the value of the enum is not equal to the value of
    // the argument
             bool        operator!=                      (const EStructureNonControlledVirtualId& rValue) const;

    // static methods for enum class objects
    static const EStructureNonControlledVirtualId invalid                      ();
    static const EStructureNonControlledVirtualId structureNonControlledVirtual();

    // This enum provides static constants that could be used in a switch
    // statements
    enum
    {
        kInvalid                       = 0,
        kStructureNonControlledVirtual = 1,
    };

private:
    // Member variable that holds the enum value
    long mValue;
};

class StructureNonControlledVirtualFactory
{
public:
    static StructureNonControlledVirtualSPtr clone(const StructureNonControlledVirtualSPtr& object);
};

// StructureBase is an immutable class - once instantiated none of the data
// fields can be changed. For the initial initialization and instantiation
// use the nested Builder class.

// Immutability is useful in multi-thread and subject observer
// applications. It makes easy creation of models with object references.

class StructureBase
{
public:
    // Use Builder to instantiate objects
    class Builder
    {
        // hide evil auto created assignment operator, no implementation
                void                 operator=(const Builder& );
    public:
        // Default constructor. All fields without default values are left
        // uninitialized. Make sure you initialize all the necessary fields
        // before instantiating
                                     Builder  ();
        // Use this constructor when you need to clone or create an object
        // just slightly different from another object
                                     Builder  (const StructureBase& object);
        // Destructor of Builder
        /*lax*/                      ~Builder ();

        // Instantiates StructureBase instance with the current
        // initialization of the fields. After the instance is ready the
        // builder could be reused to instantiate more objects. The data is
        // not reset. Second call of build() will instantiate object with
        // the same data.
                const StructureBase& build    ()                            const;

        // Provides the internal instantiated builder object and
        // invalidates the builder status. Once finalize() is called, the
        // builder can not be used again. Use finalize() when you no longer
        // are going to use this builder.
                StructureBaseSPtr    finalize ();


    protected:
        // constructor needed from potential derived classes
                                     Builder  (StructureBaseRPtr pObject);

        StructureBaseRPtr mpObject;
    };

    // Default constructor
            StructureBase ();
    // Destructor
    /*lax*/ ~StructureBase();
};

// StructureAbstract is an immutable class - once instantiated none of the
// data fields can be changed. For the initial initialization and
// instantiation use the nested Builder class.

// Immutability is useful in multi-thread and subject observer
// applications. It makes easy creation of models with object references.

class StructureAbstract : public StructureBase
{
public:
    // Default constructor
                                  StructureAbstract ();
    // Destructor
    /*lax*/                       ~StructureAbstract();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  StructureAbstractSPtr downcast          (const StructureBaseSPtr& object);
};

// StructureLeaf is an immutable class - once instantiated none of the data
// fields can be changed. For the initial initialization and instantiation
// use the nested Builder class.

// Immutability is useful in multi-thread and subject observer
// applications. It makes easy creation of models with object references.

class StructureLeaf : public StructureAbstract
{
public:
    // Use Builder to instantiate objects
    class Builder : public StructureAbstract::Builder
    {
        // hide evil auto created assignment operator, no implementation
                void                 operator=(const Builder& );
    public:
        // Default constructor. All fields without default values are left
        // uninitialized. Make sure you initialize all the necessary fields
        // before instantiating
                                     Builder  ();
        // Use this constructor when you need to clone or create an object
        // just slightly different from another object
                                     Builder  (const StructureLeaf& object);
        // Destructor of Builder
        /*lax*/                      ~Builder ();

        // Instantiates StructureLeaf instance with the current
        // initialization of the fields. After the instance is ready the
        // builder could be reused to instantiate more objects. The data is
        // not reset. Second call of build() will instantiate object with
        // the same data.
                const StructureLeaf& build    ()                            const;

        // Provides the internal instantiated builder object and
        // invalidates the builder status. Once finalize() is called, the
        // builder can not be used again. Use finalize() when you no longer
        // are going to use this builder.
                StructureLeafSPtr    finalize ();


    protected:
        // constructor needed from potential derived classes
                                     Builder  (StructureLeafRPtr pObject);
    };

    // Default constructor
                              StructureLeaf ();
    // Destructor
    /*lax*/                   ~StructureLeaf();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  StructureLeafSPtr downcast      (const StructureBaseSPtr& object);
};

#else // __GENERATOR_TEST_STRUCTURES_COMPIL_H_

// Forward declarations
class StructureIsInitialize;
typedef StructureIsInitialize*                         StructureIsInitializeRPtr;
typedef boost::shared_ptr<StructureIsInitialize>       StructureIsInitializeSPtr;
typedef boost::shared_ptr<const StructureIsInitialize> StructureIsInitializeSCPtr;
typedef boost::weak_ptr<StructureIsInitialize>         StructureIsInitializeWPtr;

class StructureIsInitialize1;
typedef StructureIsInitialize1*                         StructureIsInitialize1RPtr;
typedef boost::shared_ptr<StructureIsInitialize1>       StructureIsInitialize1SPtr;
typedef boost::shared_ptr<const StructureIsInitialize1> StructureIsInitialize1SCPtr;
typedef boost::weak_ptr<StructureIsInitialize1>         StructureIsInitialize1WPtr;

class StructureIsInitialize2;
typedef StructureIsInitialize2*                         StructureIsInitialize2RPtr;
typedef boost::shared_ptr<StructureIsInitialize2>       StructureIsInitialize2SPtr;
typedef boost::shared_ptr<const StructureIsInitialize2> StructureIsInitialize2SCPtr;
typedef boost::weak_ptr<StructureIsInitialize2>         StructureIsInitialize2WPtr;

class StructureNonControlledInherit;
typedef StructureNonControlledInherit*                         StructureNonControlledInheritRPtr;
typedef boost::shared_ptr<StructureNonControlledInherit>       StructureNonControlledInheritSPtr;
typedef boost::shared_ptr<const StructureNonControlledInherit> StructureNonControlledInheritSCPtr;
typedef boost::weak_ptr<StructureNonControlledInherit>         StructureNonControlledInheritWPtr;

class StructureIsInitialize3;
typedef StructureIsInitialize3*                         StructureIsInitialize3RPtr;
typedef boost::shared_ptr<StructureIsInitialize3>       StructureIsInitialize3SPtr;
typedef boost::shared_ptr<const StructureIsInitialize3> StructureIsInitialize3SCPtr;
typedef boost::weak_ptr<StructureIsInitialize3>         StructureIsInitialize3WPtr;

class StructureNonControlled;
typedef StructureNonControlled*                         StructureNonControlledRPtr;
typedef boost::shared_ptr<StructureNonControlled>       StructureNonControlledSPtr;
typedef boost::shared_ptr<const StructureNonControlled> StructureNonControlledSCPtr;
typedef boost::weak_ptr<StructureNonControlled>         StructureNonControlledWPtr;

class StructureIsInitialize4;
typedef StructureIsInitialize4*                         StructureIsInitialize4RPtr;
typedef boost::shared_ptr<StructureIsInitialize4>       StructureIsInitialize4SPtr;
typedef boost::shared_ptr<const StructureIsInitialize4> StructureIsInitialize4SCPtr;
typedef boost::weak_ptr<StructureIsInitialize4>         StructureIsInitialize4WPtr;

class StructureIsInitializeVirtual;
typedef StructureIsInitializeVirtual*                         StructureIsInitializeVirtualRPtr;
typedef boost::shared_ptr<StructureIsInitializeVirtual>       StructureIsInitializeVirtualSPtr;
typedef boost::shared_ptr<const StructureIsInitializeVirtual> StructureIsInitializeVirtualSCPtr;
typedef boost::weak_ptr<StructureIsInitializeVirtual>         StructureIsInitializeVirtualWPtr;

class EStructureIsInitializeVirtualId;

class StructureNonControlledVirtualInherit;
typedef StructureNonControlledVirtualInherit*                         StructureNonControlledVirtualInheritRPtr;
typedef boost::shared_ptr<StructureNonControlledVirtualInherit>       StructureNonControlledVirtualInheritSPtr;
typedef boost::shared_ptr<const StructureNonControlledVirtualInherit> StructureNonControlledVirtualInheritSCPtr;
typedef boost::weak_ptr<StructureNonControlledVirtualInherit>         StructureNonControlledVirtualInheritWPtr;

class StructureIsInitialize5;
typedef StructureIsInitialize5*                         StructureIsInitialize5RPtr;
typedef boost::shared_ptr<StructureIsInitialize5>       StructureIsInitialize5SPtr;
typedef boost::shared_ptr<const StructureIsInitialize5> StructureIsInitialize5SCPtr;
typedef boost::weak_ptr<StructureIsInitialize5>         StructureIsInitialize5WPtr;

class StructureNonControlledVirtual;
typedef StructureNonControlledVirtual*                         StructureNonControlledVirtualRPtr;
typedef boost::shared_ptr<StructureNonControlledVirtual>       StructureNonControlledVirtualSPtr;
typedef boost::shared_ptr<const StructureNonControlledVirtual> StructureNonControlledVirtualSCPtr;
typedef boost::weak_ptr<StructureNonControlledVirtual>         StructureNonControlledVirtualWPtr;

class EStructureNonControlledVirtualId;

class StructureIsInitialize6;
typedef StructureIsInitialize6*                         StructureIsInitialize6RPtr;
typedef boost::shared_ptr<StructureIsInitialize6>       StructureIsInitialize6SPtr;
typedef boost::shared_ptr<const StructureIsInitialize6> StructureIsInitialize6SCPtr;
typedef boost::weak_ptr<StructureIsInitialize6>         StructureIsInitialize6WPtr;

class StructureIsVoid;
typedef StructureIsVoid*                         StructureIsVoidRPtr;
typedef boost::shared_ptr<StructureIsVoid>       StructureIsVoidSPtr;
typedef boost::shared_ptr<const StructureIsVoid> StructureIsVoidSCPtr;
typedef boost::weak_ptr<StructureIsVoid>         StructureIsVoidWPtr;

class StructureIsVoid1;
typedef StructureIsVoid1*                         StructureIsVoid1RPtr;
typedef boost::shared_ptr<StructureIsVoid1>       StructureIsVoid1SPtr;
typedef boost::shared_ptr<const StructureIsVoid1> StructureIsVoid1SCPtr;
typedef boost::weak_ptr<StructureIsVoid1>         StructureIsVoid1WPtr;

class StructureIsInitializeVirtualFactory;
typedef StructureIsInitializeVirtualFactory*                         StructureIsInitializeVirtualFactoryRPtr;
typedef boost::shared_ptr<StructureIsInitializeVirtualFactory>       StructureIsInitializeVirtualFactorySPtr;
typedef boost::shared_ptr<const StructureIsInitializeVirtualFactory> StructureIsInitializeVirtualFactorySCPtr;
typedef boost::weak_ptr<StructureIsInitializeVirtualFactory>         StructureIsInitializeVirtualFactoryWPtr;

class EStructureIsInitializeVirtualId;
typedef EStructureIsInitializeVirtualId*                         StructureIsInitializeVirtualIdRPtr;
typedef boost::shared_ptr<EStructureIsInitializeVirtualId>       StructureIsInitializeVirtualIdSPtr;
typedef boost::shared_ptr<const EStructureIsInitializeVirtualId> StructureIsInitializeVirtualIdSCPtr;
typedef boost::weak_ptr<EStructureIsInitializeVirtualId>         StructureIsInitializeVirtualIdWPtr;

class StructureIsInitializeVirtualFactory;

class StructureNonControlledVirtualFactory;
typedef StructureNonControlledVirtualFactory*                         StructureNonControlledVirtualFactoryRPtr;
typedef boost::shared_ptr<StructureNonControlledVirtualFactory>       StructureNonControlledVirtualFactorySPtr;
typedef boost::shared_ptr<const StructureNonControlledVirtualFactory> StructureNonControlledVirtualFactorySCPtr;
typedef boost::weak_ptr<StructureNonControlledVirtualFactory>         StructureNonControlledVirtualFactoryWPtr;

class EStructureNonControlledVirtualId;
typedef EStructureNonControlledVirtualId*                         StructureNonControlledVirtualIdRPtr;
typedef boost::shared_ptr<EStructureNonControlledVirtualId>       StructureNonControlledVirtualIdSPtr;
typedef boost::shared_ptr<const EStructureNonControlledVirtualId> StructureNonControlledVirtualIdSCPtr;
typedef boost::weak_ptr<EStructureNonControlledVirtualId>         StructureNonControlledVirtualIdWPtr;

class StructureNonControlledVirtualFactory;

class StructureBase;
typedef StructureBase*                         StructureBaseRPtr;
typedef boost::shared_ptr<StructureBase>       StructureBaseSPtr;
typedef boost::shared_ptr<const StructureBase> StructureBaseSCPtr;
typedef boost::weak_ptr<StructureBase>         StructureBaseWPtr;

class StructureAbstract;
typedef StructureAbstract*                         StructureAbstractRPtr;
typedef boost::shared_ptr<StructureAbstract>       StructureAbstractSPtr;
typedef boost::shared_ptr<const StructureAbstract> StructureAbstractSCPtr;
typedef boost::weak_ptr<StructureAbstract>         StructureAbstractWPtr;

class StructureLeaf;
typedef StructureLeaf*                         StructureLeafRPtr;
typedef boost::shared_ptr<StructureLeaf>       StructureLeafSPtr;
typedef boost::shared_ptr<const StructureLeaf> StructureLeafSCPtr;
typedef boost::weak_ptr<StructureLeaf>         StructureLeafWPtr;

#endif // __GENERATOR_TEST_STRUCTURES_COMPIL_H_

