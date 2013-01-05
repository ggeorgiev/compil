#ifndef __CORE_FLAGS_ENUMERATION_HPP_H_
#define __CORE_FLAGS_ENUMERATION_HPP_H_

template<class T, class F>
class flags_enumeration
{
public:
    // Default constructor - sets the value to invalid
    flags_enumeration()
        : mValue(0)
    {
    }

    flags_enumeration(T value)
        : mValue(value)
    {
    }

    T value() const
    {
        return mValue;
    }

    // Resets the flags included in the mask to the state in value
    void reset(const F& mask, const F& value)
    {
        mValue = value.value() | (this->value() & ~mask.value());
    }

    // Sets the flags included in the mask. Equivalent to reset(mask, all).
    void set(const F& mask)
    {
        mValue |= mask.value();
    }

    // Clears the flags included in the mask. Equivalent to reset(mask,
    // nil).
    void clear(const F& mask)
    {
        mValue &= ~mask.value();
    }

    // Turns the flags included in the mask.
    void turn(const F& mask)
    {
        mValue ^= mask.value();
    }

    // Returns assemble of the current flags with the flags from the mask
    // to the state in value. This is immutable version of reset.
    F assemble(const F& mask, const F& value) const
    {
        return F(value.value() | (this->value() & ~mask.value()));
    }

    // Returns combination of the flags included in the mask. This is
    // immutable version of set.
    F combine(const F& mask) const
    {
        return F(value() | mask.value());
    }

    // Returns intersection of the flags included in the mask. This is
    // immutable version of clear.
    F intersect(const F& mask) const
    {
        return F(value() & ~mask.value());
    }

    // Returns flipped the flags included in the mask. This is immutable
    // version of turn.
    F flip(const F& mask) const
    {
        return F(value() ^ mask.value());
    }

    // Tests if the flags included in the mask are the same state as state
    // in value
    bool test(const F& mask, const F& value) const
    {
        return (this->value() & mask.value()) == value.value();
    }

    // Tests if the flags included in the mask are set. Equivalent to
    // test(mask, all).
    bool isSet(const F& mask) const
    {
        return (value() & mask.value()) == mask.value();
    }

    // Tests if the flags included in the mask are clear. Equivalent to
    // test(mask, nil).
    bool isClear(const F& mask) const
    {
        return (value() & mask.value()) == 0;
    }

protected:
    T mValue;
};

#endif // __CORE_FLAGS_ENUMERATION_HPP_H_

