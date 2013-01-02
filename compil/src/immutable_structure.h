// Boost C++ Smart Pointers
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
// Standard Template Library
#include <string>

#ifndef __GENERATOR_TEST_IMMUTABLE_STRUCTURE_COMPIL_H_
#define __GENERATOR_TEST_IMMUTABLE_STRUCTURE_COMPIL_H_

#include "generator-test/immutable_structure.h"
#include "immutable_structure.h"

// ImmutableStructure1 is an immutable class - once instantiated none of
// the data fields can be changed. For the initial initialization and
// instantiation use the nested Builder class.

// Immutability is useful in multi-thread and subject observer
// applications. It makes easy creation of models with object references.

class ImmutableStructure1
{
public:
    // Use Builder to instantiate objects
    class Builder
    {
        // hide evil auto created assignment operator, no implementation
                void                       operator= (const Builder& );
    public:
        // Default constructor. All fields without default values are left
        // uninitialized. Make sure you initialize all the necessary fields
        // before instantiating
                                           Builder   ();
        // Use this constructor when you need to clone or create an object
        // just slightly different from another object
                                           Builder   (const ImmutableStructure1& object);
        // Destructor of Builder
        /*lax*/                            ~Builder  ();

        // Instantiates ImmutableStructure1 instance with the current
        // initialization of the fields. After the instance is ready the
        // builder could be reused to instantiate more objects. The data is
        // not reset. Second call of build() will instantiate object with
        // the same data.
                const ImmutableStructure1& build     ()                                  const;

        // Provides the internal instantiated builder object and
        // invalidates the builder status. Once finalize() is called, the
        // builder can not be used again. Use finalize() when you no longer
        // are going to use this builder.
                ImmutableStructure1SPtr    finalize  ();


        // Setter method for the data field r1
                Builder&                   set_r1    (long r1);
        // Erases the required data field r1. Object can not be
        // instantiated before the field data is set again
                void                       erase_r1  ();

        // Setter method for the data field o1
                Builder&                   set_o1    (long o1);
        // Clears the optional data field o1
                void                       clear_o1  ();

        // Setter method for the data field d1
                Builder&                   set_d1    (long d1);
        // Updates the data field d1. If the new value is equal to the
        // default it clears the field else it sets it to the new value
                Builder&                   update_d1 (long d1);
        // Resets the data field d1 to its default value 1
                void                       reset_d1  ();

        // Setter method for the data field s1
                Builder&                   set_s1    (const std::string& s1);
        // Provides mutable access to field s1
                std::string&               mutable_s1();
        // Erases the required data field s1. Object can not be
        // instantiated before the field data is set again
                void                       erase_s1  ();

    protected:
        // constructor needed from potential derived classes
                                           Builder   (ImmutableStructure1RPtr pObject);

        ImmutableStructure1RPtr mpObject;
    };

    // Default constructor
                               ImmutableStructure1 ();
    // Destructor
    /*lax*/                    ~ImmutableStructure1();

    // Returns true if every required field is initialized.
    // Note: If the class is used properly it should always return true,
    // because the object could be instantiated only if it is already
    // initialized and can not be changed. Called by the Builder class.
            bool               isInitialized       () const;

    // Getter method for the data field r1
            long               r1                  () const;
    // Returns true if the data field r1 was set and could be considered
    // valid
    // Note: If the class is used properly it should always return true. It
    // makes sense when it is called indirectly through isInitialized()
    // from the Builder class
            bool               valid_r1            () const;

    // Getter method for the data field o1
            long               o1                  () const;
    // Checks if the optional field o1 exists
            bool               exist_o1            () const;

    // Getter method for the data field d1
            long               d1                  () const;
    // Returns true if the data field value d1 was changed from its default
    // value 1
            bool               changed_d1          () const;
    // Returns the default value 1 of the field d1
    static  long               default_d1          ();

    // Getter method for the data field s1
            const std::string& s1                  () const;
    // Returns true if the data field s1 was set and could be considered
    // valid
    // Note: If the class is used properly it should always return true. It
    // makes sense when it is called indirectly through isInitialized()
    // from the Builder class
            bool               valid_s1            () const;

private:
    // Returns unique bitmask value for the field r1
    static int bitmask_r1();
    // Returns unique bitmask value for the field o1
    static int bitmask_o1();
    // Returns unique bitmask value for the field d1
    static int bitmask_d1();
    // Returns unique bitmask value for the field s1
    static int bitmask_s1();

    // Stores availability information for the fields
    int         mBits;

    // variable for the data field r1
    long        mR1;
    // variable for the data field o1
    long        mO1;
    // variable for the data field d1
    long        mD1;
    // variable for the data field s1
    std::string mS1;
};

// ImmutableStructure2 is an immutable class - once instantiated none of
// the data fields can be changed. For the initial initialization and
// instantiation use the nested Builder class.

// Immutability is useful in multi-thread and subject observer
// applications. It makes easy creation of models with object references.

class ImmutableStructure2 : public ImmutableStructure1
{
public:
    // Use Builder to instantiate objects
    class Builder : public ImmutableStructure1::Builder
    {
        // hide evil auto created assignment operator, no implementation
                void                       operator= (const Builder& );
    public:
        // Default constructor. All fields without default values are left
        // uninitialized. Make sure you initialize all the necessary fields
        // before instantiating
                                           Builder   ();
        // Use this constructor when you need to clone or create an object
        // just slightly different from another object
                                           Builder   (const ImmutableStructure2& object);
        // Destructor of Builder
        /*lax*/                            ~Builder  ();

        // Instantiates ImmutableStructure2 instance with the current
        // initialization of the fields. After the instance is ready the
        // builder could be reused to instantiate more objects. The data is
        // not reset. Second call of build() will instantiate object with
        // the same data.
                const ImmutableStructure2& build     ()                                  const;

        // Provides the internal instantiated builder object and
        // invalidates the builder status. Once finalize() is called, the
        // builder can not be used again. Use finalize() when you no longer
        // are going to use this builder.
                ImmutableStructure2SPtr    finalize  ();


        // Setter method for the data field r1
                Builder&                   set_r1    (long r1);

        // Setter method for the data field o1
                Builder&                   set_o1    (long o1);

        // Setter method for the data field d1
                Builder&                   set_d1    (long d1);

        // Setter method for the data field s1
                Builder&                   set_s1    (const std::string& s1);

        // Setter method for the data field r2
                Builder&                   set_r2    (long r2);
        // Erases the required data field r2. Object can not be
        // instantiated before the field data is set again
                void                       erase_r2  ();

        // Setter method for the data field o2
                Builder&                   set_o2    (long o2);
        // Clears the optional data field o2
                void                       clear_o2  ();

        // Setter method for the data field d2
                Builder&                   set_d2    (long d2);
        // Updates the data field d2. If the new value is equal to the
        // default it clears the field else it sets it to the new value
                Builder&                   update_d2 (long d2);
        // Resets the data field d2 to its default value 2
                void                       reset_d2  ();

        // Setter method for the data field s2
                Builder&                   set_s2    (const std::string& s2);
        // Provides mutable access to field s2
                std::string&               mutable_s2();
        // Erases the required data field s2. Object can not be
        // instantiated before the field data is set again
                void                       erase_s2  ();

    protected:
        // constructor needed from potential derived classes
                                           Builder   (ImmutableStructure2RPtr pObject);
    };

    // Default constructor
                                    ImmutableStructure2 ();
    // Destructor
    /*lax*/                         ~ImmutableStructure2();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  ImmutableStructure2SPtr downcast            (const ImmutableStructure1SPtr& object);

    // Returns true if every required field is initialized.
    // Note: If the class is used properly it should always return true,
    // because the object could be instantiated only if it is already
    // initialized and can not be changed. Called by the Builder class.
            bool                    isInitialized       ()                                      const;

    // Getter method for the data field r2
            long                    r2                  ()                                      const;
    // Returns true if the data field r2 was set and could be considered
    // valid
    // Note: If the class is used properly it should always return true. It
    // makes sense when it is called indirectly through isInitialized()
    // from the Builder class
            bool                    valid_r2            ()                                      const;

    // Getter method for the data field o2
            long                    o2                  ()                                      const;
    // Checks if the optional field o2 exists
            bool                    exist_o2            ()                                      const;

    // Getter method for the data field d2
            long                    d2                  ()                                      const;
    // Returns true if the data field value d2 was changed from its default
    // value 2
            bool                    changed_d2          ()                                      const;
    // Returns the default value 2 of the field d2
    static  long                    default_d2          ();

    // Getter method for the data field s2
            const std::string&      s2                  ()                                      const;
    // Returns true if the data field s2 was set and could be considered
    // valid
    // Note: If the class is used properly it should always return true. It
    // makes sense when it is called indirectly through isInitialized()
    // from the Builder class
            bool                    valid_s2            ()                                      const;

    // Setter method for the data field r1
            ImmutableStructure2&    set_r1              (long r1);

    // Setter method for the data field o1
            ImmutableStructure2&    set_o1              (long o1);

    // Setter method for the data field d1
            ImmutableStructure2&    set_d1              (long d1);

    // Setter method for the data field s1
            ImmutableStructure2&    set_s1              (const std::string& s1);

private:
    // Returns unique bitmask value for the field r2
    static int bitmask_r2();
    // Returns unique bitmask value for the field o2
    static int bitmask_o2();
    // Returns unique bitmask value for the field d2
    static int bitmask_d2();
    // Returns unique bitmask value for the field s2
    static int bitmask_s2();

    // Stores availability information for the fields
    int         mBits;

    // variable for the data field r2
    long        mR2;
    // variable for the data field o2
    long        mO2;
    // variable for the data field d2
    long        mD2;
    // variable for the data field s2
    std::string mS2;
};

// ImmutableStructure3 is an immutable class - once instantiated none of
// the data fields can be changed. For the initial initialization and
// instantiation use the nested Builder class.

// Immutability is useful in multi-thread and subject observer
// applications. It makes easy creation of models with object references.

class ImmutableStructure3 : public ImmutableStructure2
{
public:
    // Use Builder to instantiate objects
    class Builder : public ImmutableStructure2::Builder
    {
        // hide evil auto created assignment operator, no implementation
                void                       operator= (const Builder& );
    public:
        // Default constructor. All fields without default values are left
        // uninitialized. Make sure you initialize all the necessary fields
        // before instantiating
                                           Builder   ();
        // Use this constructor when you need to clone or create an object
        // just slightly different from another object
                                           Builder   (const ImmutableStructure3& object);
        // Destructor of Builder
        /*lax*/                            ~Builder  ();

        // Instantiates ImmutableStructure3 instance with the current
        // initialization of the fields. After the instance is ready the
        // builder could be reused to instantiate more objects. The data is
        // not reset. Second call of build() will instantiate object with
        // the same data.
                const ImmutableStructure3& build     ()                                  const;

        // Provides the internal instantiated builder object and
        // invalidates the builder status. Once finalize() is called, the
        // builder can not be used again. Use finalize() when you no longer
        // are going to use this builder.
                ImmutableStructure3SPtr    finalize  ();


        // Setter method for the data field r1
                Builder&                   set_r1    (long r1);

        // Setter method for the data field o1
                Builder&                   set_o1    (long o1);

        // Setter method for the data field d1
                Builder&                   set_d1    (long d1);

        // Setter method for the data field s1
                Builder&                   set_s1    (const std::string& s1);

        // Setter method for the data field r2
                Builder&                   set_r2    (long r2);

        // Setter method for the data field o2
                Builder&                   set_o2    (long o2);

        // Setter method for the data field d2
                Builder&                   set_d2    (long d2);

        // Setter method for the data field s2
                Builder&                   set_s2    (const std::string& s2);

        // Setter method for the data field r3
                Builder&                   set_r3    (long r3);
        // Erases the required data field r3. Object can not be
        // instantiated before the field data is set again
                void                       erase_r3  ();

        // Setter method for the data field o3
                Builder&                   set_o3    (long o3);
        // Clears the optional data field o3
                void                       clear_o3  ();

        // Setter method for the data field d3
                Builder&                   set_d3    (long d3);
        // Updates the data field d3. If the new value is equal to the
        // default it clears the field else it sets it to the new value
                Builder&                   update_d3 (long d3);
        // Resets the data field d3 to its default value 3
                void                       reset_d3  ();

        // Setter method for the data field s3
                Builder&                   set_s3    (const std::string& s3);
        // Provides mutable access to field s3
                std::string&               mutable_s3();
        // Erases the required data field s3. Object can not be
        // instantiated before the field data is set again
                void                       erase_s3  ();

    protected:
        // constructor needed from potential derived classes
                                           Builder   (ImmutableStructure3RPtr pObject);
    };

    // Default constructor
                                    ImmutableStructure3 ();
    // Destructor
    /*lax*/                         ~ImmutableStructure3();

    // Downcast method is syntactic sugar for boost::static_pointer_cast.
    // Note that it does not provide any type checks. Use it on your own
    // risk.
    static  ImmutableStructure3SPtr downcast            (const ImmutableStructure1SPtr& object);

    // Returns true if every required field is initialized.
    // Note: If the class is used properly it should always return true,
    // because the object could be instantiated only if it is already
    // initialized and can not be changed. Called by the Builder class.
            bool                    isInitialized       ()                                      const;

    // Getter method for the data field r3
            long                    r3                  ()                                      const;
    // Returns true if the data field r3 was set and could be considered
    // valid
    // Note: If the class is used properly it should always return true. It
    // makes sense when it is called indirectly through isInitialized()
    // from the Builder class
            bool                    valid_r3            ()                                      const;

    // Getter method for the data field o3
            long                    o3                  ()                                      const;
    // Checks if the optional field o3 exists
            bool                    exist_o3            ()                                      const;

    // Getter method for the data field d3
            long                    d3                  ()                                      const;
    // Returns true if the data field value d3 was changed from its default
    // value 3
            bool                    changed_d3          ()                                      const;
    // Returns the default value 3 of the field d3
    static  long                    default_d3          ();

    // Getter method for the data field s3
            const std::string&      s3                  ()                                      const;
    // Returns true if the data field s3 was set and could be considered
    // valid
    // Note: If the class is used properly it should always return true. It
    // makes sense when it is called indirectly through isInitialized()
    // from the Builder class
            bool                    valid_s3            ()                                      const;

    // Setter method for the data field r1
            ImmutableStructure3&    set_r1              (long r1);

    // Setter method for the data field o1
            ImmutableStructure3&    set_o1              (long o1);

    // Setter method for the data field d1
            ImmutableStructure3&    set_d1              (long d1);

    // Setter method for the data field s1
            ImmutableStructure3&    set_s1              (const std::string& s1);

    // Setter method for the data field r2
            ImmutableStructure3&    set_r2              (long r2);

    // Setter method for the data field o2
            ImmutableStructure3&    set_o2              (long o2);

    // Setter method for the data field d2
            ImmutableStructure3&    set_d2              (long d2);

    // Setter method for the data field s2
            ImmutableStructure3&    set_s2              (const std::string& s2);

private:
    // Returns unique bitmask value for the field r3
    static int bitmask_r3();
    // Returns unique bitmask value for the field o3
    static int bitmask_o3();
    // Returns unique bitmask value for the field d3
    static int bitmask_d3();
    // Returns unique bitmask value for the field s3
    static int bitmask_s3();

    // Stores availability information for the fields
    int         mBits;

    // variable for the data field r3
    long        mR3;
    // variable for the data field o3
    long        mO3;
    // variable for the data field d3
    long        mD3;
    // variable for the data field s3
    std::string mS3;
};

// ImmutableStructureAggregate is an immutable class - once instantiated
// none of the data fields can be changed. For the initial initialization
// and instantiation use the nested Builder class.

// Immutability is useful in multi-thread and subject observer
// applications. It makes easy creation of models with object references.

class ImmutableStructureAggregate
{
public:
    // Use Builder to instantiate objects
    class Builder
    {
        // hide evil auto created assignment operator, no implementation
                void                               operator= (const Builder& );
    public:
        // Default constructor. All fields without default values are left
        // uninitialized. Make sure you initialize all the necessary fields
        // before instantiating
                                                   Builder   ();
        // Use this constructor when you need to clone or create an object
        // just slightly different from another object
                                                   Builder   (const ImmutableStructureAggregate& object);
        // Destructor of Builder
        /*lax*/                                    ~Builder  ();

        // Instantiates ImmutableStructureAggregate instance with the
        // current initialization of the fields. After the instance is
        // ready the builder could be reused to instantiate more objects.
        // The data is not reset. Second call of build() will instantiate
        // object with the same data.
                const ImmutableStructureAggregate& build     ()                                          const;

        // Provides the internal instantiated builder object and
        // invalidates the builder status. Once finalize() is called, the
        // builder can not be used again. Use finalize() when you no longer
        // are going to use this builder.
                ImmutableStructureAggregateSPtr    finalize  ();


        // Setter method for the data field rs
                Builder&                           set_rs    (const ImmutableStructure1& rs);
        // Provides mutable access to field rs
                ImmutableStructure1&               mutable_rs();
        // Erases the required data field rs. Object can not be
        // instantiated before the field data is set again
                void                               erase_rs  ();

        // Setter method for the data field os
                Builder&                           set_os    (const ImmutableStructure1& os);
        // Provides mutable access to field os
                ImmutableStructure1&               mutable_os();
        // Clears the optional data field os
                void                               clear_os  ();

        // Setter method for the data field rrs
                Builder&                           set_rrs   (const ImmutableStructure1SPtr& rrs);
        // Erases the required data field rrs. Object can not be
        // instantiated before the field data is set again
                void                               erase_rrs ();

        // Setter method for the data field ors
                Builder&                           set_ors   (const ImmutableStructure1SPtr& ors);
        // Clears the optional data field ors
                void                               clear_ors ();

        // Setter method for the data field rns
                Builder&                           set_rns   (const ImmutableStructure1SPtr& rns);
        // Updates the data field rns. If the new value is equal to the
        // default it clears the field else it sets it to the new value
                Builder&                           update_rns(const ImmutableStructure1SPtr& rns);
        // Resets the data field rns to its default value null
                void                               reset_rns ();

    protected:
        // constructor needed from potential derived classes
                                                   Builder   (ImmutableStructureAggregateRPtr pObject);

        ImmutableStructureAggregateRPtr mpObject;
    };

    // Default constructor
                                           ImmutableStructureAggregate ();
    // Destructor
    /*lax*/                                ~ImmutableStructureAggregate();

    // Returns true if every required field is initialized.
    // Note: If the class is used properly it should always return true,
    // because the object could be instantiated only if it is already
    // initialized and can not be changed. Called by the Builder class.
            bool                           isInitialized               () const;

    // Getter method for the data field rs
            const ImmutableStructure1&     rs                          () const;
    // Returns true if the data field rs was set and could be considered
    // valid
    // Note: If the class is used properly it should always return true. It
    // makes sense when it is called indirectly through isInitialized()
    // from the Builder class
            bool                           valid_rs                    () const;

    // Getter method for the data field os
            const ImmutableStructure1&     os                          () const;
    // Checks if the optional field os exists
            bool                           exist_os                    () const;

    // Getter method for the data field rrs
            const ImmutableStructure1SPtr& rrs                         () const;
    // Returns true if the data field rrs was set and could be considered
    // valid
    // Note: If the class is used properly it should always return true. It
    // makes sense when it is called indirectly through isInitialized()
    // from the Builder class
            bool                           valid_rrs                   () const;

    // Getter method for the data field ors
            const ImmutableStructure1SPtr& ors                         () const;
    // Checks if the optional field ors exists
            bool                           exist_ors                   () const;

    // Getter method for the data field rns
            const ImmutableStructure1SPtr& rns                         () const;
    // Returns true if the data field value rns was changed from its
    // default value null
            bool                           changed_rns                 () const;
    // Returns the default value null of the field rns
    static  ImmutableStructure1SPtr        default_rns                 ();

private:
    // Returns unique bitmask value for the field rs
    static int bitmask_rs ();
    // Returns unique bitmask value for the field os
    static int bitmask_os ();
    // Returns unique bitmask value for the field rrs
    static int bitmask_rrs();
    // Returns unique bitmask value for the field ors
    static int bitmask_ors();
    // Returns unique bitmask value for the field rns
    static int bitmask_rns();

    // Stores availability information for the fields
    int                     mBits;

    // variable for the data field rs
    ImmutableStructure1     mRs;
    // variable for the data field os
    ImmutableStructure1     mOs;
    // variable for the data field rrs
    ImmutableStructure1SPtr mRrs;
    // variable for the data field ors
    ImmutableStructure1SPtr mOrs;
    // variable for the data field rns
    ImmutableStructure1SPtr mRns;
};

#else // __GENERATOR_TEST_IMMUTABLE_STRUCTURE_COMPIL_H_

// Forward declarations
class ImmutableStructure1;
typedef ImmutableStructure1*                         ImmutableStructure1RPtr;
typedef boost::shared_ptr<ImmutableStructure1>       ImmutableStructure1SPtr;
typedef boost::shared_ptr<const ImmutableStructure1> ImmutableStructure1SCPtr;
typedef boost::weak_ptr<ImmutableStructure1>         ImmutableStructure1WPtr;

class ImmutableStructure2;
typedef ImmutableStructure2*                         ImmutableStructure2RPtr;
typedef boost::shared_ptr<ImmutableStructure2>       ImmutableStructure2SPtr;
typedef boost::shared_ptr<const ImmutableStructure2> ImmutableStructure2SCPtr;
typedef boost::weak_ptr<ImmutableStructure2>         ImmutableStructure2WPtr;

class ImmutableStructure3;
typedef ImmutableStructure3*                         ImmutableStructure3RPtr;
typedef boost::shared_ptr<ImmutableStructure3>       ImmutableStructure3SPtr;
typedef boost::shared_ptr<const ImmutableStructure3> ImmutableStructure3SCPtr;
typedef boost::weak_ptr<ImmutableStructure3>         ImmutableStructure3WPtr;

class ImmutableStructureAggregate;
typedef ImmutableStructureAggregate*                         ImmutableStructureAggregateRPtr;
typedef boost::shared_ptr<ImmutableStructureAggregate>       ImmutableStructureAggregateSPtr;
typedef boost::shared_ptr<const ImmutableStructureAggregate> ImmutableStructureAggregateSCPtr;
typedef boost::weak_ptr<ImmutableStructureAggregate>         ImmutableStructureAggregateWPtr;

#endif // __GENERATOR_TEST_IMMUTABLE_STRUCTURE_COMPIL_H_

