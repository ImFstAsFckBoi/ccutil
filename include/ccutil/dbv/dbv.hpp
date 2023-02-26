#include <string>
#include <concepts>
#include <fstream>
#include <iostream>

using byte_t = uint8_t;


namespace cc
{

/**
 * @brief Disk-Bound-Variable. Variables that sync to a file.
 * Like a database, but dumb.
 * 
 * @tparam T Standard layout type.
 */
template <typename T>
    requires std::is_standard_layout_v<T> && std::is_trivial_v<T>
class dbv
{
public:
    /**
     * @brief Construct a new dbv object.
     * 
     * @param path File path to store data in.
     * @param sync_frequency How often to write changes. 0 = never, 1 = always, n = every n changes.
     */
    dbv(const std::string &path, size_t sync_frequency = 0)
        : store_on_dtor{true}, __value{}, __path{path}, __sync_freq{sync_frequency}, __tick{0}
    {
        std::ifstream file(__path);
        if (file.good())
            load();
        else
            store();
    }
    /**
     * @brief Destroy the dbv object.
     * 
     */
    ~dbv()
    {
        if (store_on_dtor)
            store();
    }
    /**
     * @brief Load value from disk to memory.
     * 
     * @return const T& Immutable to newly fetch value.
     */
    const T &load()
    {
        byte_t *value_p = reinterpret_cast<byte_t *>(&__value);

        std::cerr << "Before: ";
        for (int i{}; i < sizeof(T); ++i)
        {
            std::cerr << (int)*(value_p + i) << " ";
        }
        std::cerr << "\n" << std::endl;

        std::ifstream ifs(__path);
        std::cerr << "Reading " << sizeof(T) << " bytes from " << __path <<std::endl;
        for (int i{}; i < sizeof(T); ++i)
        {
            byte_t a;
            ifs >> a;
            std::cerr << "Reading: " << (int) a << " position " << i << std::endl;
            *(value_p + i) = a;
        }

        std::cerr << "Result: ";
        for (int i{}; i < sizeof(T); ++i)
        {
            std::cerr << (int)*(value_p + i) << " ";
        }
        std::cerr << "\n" << std::endl;
        return __value;
    }
    /**
     * @brief Store value from memory to disk.
     * 
     */
    void store()
    {
        __tick = 0;
        byte_t *value_p = reinterpret_cast<byte_t *>(&__value);
        std::ofstream ofs{__path};
        std::cerr << "Writing " << sizeof(T) << " bytes to " << __path << std::endl;
        for (int i{}; i < sizeof(T); ++i)
        {
            std::cerr << "Writing: " << (int) *(value_p + i) << " position " << i << std::endl;
            ofs << *(value_p + i) << std::flush;
            std::ifstream ifs{__path};
            std::cerr << "Confirming content: ";
            for (int j{}; j < i; ++j)
            {
                byte_t a;
                ifs >> a;
                std::cerr << (int) a << " ";
            }
            std::cerr << std::endl;
        }
    }
    /**
     * @brief Change value and store it directly.
     * Functionally same as set(new_value); store();
     *
     * @param new_value New value to set and store.
     */
    void store(const T &new_value)
    {
        __value = new_value;
        store();
    }
    /**
     * @brief Get a immutable reference to the in-memory value without loading from disk.
     * 
     * @return const T& In-memory value.
     */
    const T &get()
    { return __value; }
    /**
     * @brief Set the in-memory value.
     * Sync occasionally according to constructor parameter sync_frequency
     * 
     * @param new_value New value to set.
     */
    void set(const T &new_value)
    {
        __value = new_value;
        __sync_tick();
    }

    bool store_on_dtor;

private:
    T __value;
    std::string __path;
    size_t __sync_freq;
    int __tick;

    void __sync_tick()
    {
        if (__sync_freq == 0)
            return;
        
        if (++__tick == __sync_freq)
        {
            __tick = 0;
            store();
        }
    }
};

} // NAMESPACE CC
