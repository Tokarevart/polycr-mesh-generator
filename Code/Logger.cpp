#include "Logger.h"

using tva::Logger;




void Logger::flush()
{
    if (m_turnFlag != 0)
    {
        if (m_turnFlag == 1)
            m_values.push_back("");
        m_endings.push_back("");
    }

    size_t max_descriptions_size = 0ull;
    for (size_t i = 0ull, buf, max = m_descriptions.size(); i < max; i++)
    {
        buf = m_descriptions[i].size();
        if (buf > max_descriptions_size)
            max_descriptions_size = buf;
    }

    size_t extended_line_description_size = max_descriptions_size + 6ull;
    size_t records_number = m_descriptions.size();

    for (size_t i = 0ull; i < records_number; i++)
    {
        m_file << ">>  " + m_descriptions[i] + std::string(extended_line_description_size - m_descriptions[i].size(), '.')
            + ">>  " + m_values[i] + ' ' + m_endings[i] << '\n';
    }
}




Logger::Iomanip Logger::setw(std::streamsize new_width)
{
    return Iomanip{ WIDTH, new_width };
}

Logger::Iomanip Logger::setprecision(std::streamsize new_precision)
{
    return Iomanip{ PRECISION, new_precision };
}




bool Logger::isOpen() const
{
    return m_file.is_open();
}


void Logger::open(const std::string& filename, std::ios::openmode mode)
{
    m_file.open(filename, mode);
}


void Logger::close()
{
    flush();
    clear();
    m_file.close();
}


void Logger::clear()
{
    m_descriptions.clear();
    m_values.clear();
    m_endings.clear();
}


std::streamsize Logger::width() const
{
    return m_bufiss->width();
}


std::streamsize Logger::width(std::streamsize new_width)
{
    return m_bufiss->width(new_width);
}


std::streamsize Logger::precision() const
{
    return m_bufiss->precision();
}


std::streamsize Logger::precision(std::streamsize new_precision)
{
    return m_bufiss->precision(new_precision);
}


std::ios::fmtflags Logger::setf(std::ios::fmtflags flags)
{
    return m_bufiss->setf(flags);
}


std::ios::fmtflags Logger::setf(std::ios::fmtflags flags, std::ios::fmtflags mask)
{
    return m_bufiss->setf(flags, mask);
}




Logger& Logger::operator<<(short value)
{
    if (m_turnFlag != 1)
        throw std::logic_error("Wrong input order.\nError in function: Logger::operator<<");

    *m_bufiss << value;
    m_values.push_back(m_bufiss->str());
    std::ios::fmtflags fmtflags_buf = m_bufiss->flags();
    m_bufiss.reset(new std::stringstream(std::ios::in | std::ios::out));
    m_bufiss->flags(fmtflags_buf);

    m_turnFlag++;
    return *this;
}


Logger& Logger::operator<<(unsigned short value)
{
    if (m_turnFlag != 1)
        throw std::logic_error("Wrong input order.\nError in function: Logger::operator<<");

    *m_bufiss << value;
    m_values.push_back(m_bufiss->str());
    std::ios::fmtflags fmtflags_buf = m_bufiss->flags();
    m_bufiss.reset(new std::stringstream(std::ios::in | std::ios::out));
    m_bufiss->flags(fmtflags_buf);

    m_turnFlag++;
    return *this;
}


Logger& Logger::operator<<(int value)
{
    if (m_turnFlag != 1)
        throw std::logic_error("Wrong input order.\nError in function: Logger::operator<<");

    *m_bufiss << value;
    m_values.push_back(m_bufiss->str());
    std::ios::fmtflags fmtflags_buf = m_bufiss->flags();
    m_bufiss.reset(new std::stringstream(std::ios::in | std::ios::out));
    m_bufiss->flags(fmtflags_buf);

    m_turnFlag++;
    return *this;
}


Logger& Logger::operator<<(unsigned int value)
{
    if (m_turnFlag != 1)
        throw std::logic_error("Wrong input order.\nError in function: Logger::operator<<");

    *m_bufiss << value;
    m_values.push_back(m_bufiss->str());
    std::ios::fmtflags fmtflags_buf = m_bufiss->flags();
    m_bufiss.reset(new std::stringstream(std::ios::in | std::ios::out));
    m_bufiss->flags(fmtflags_buf);

    m_turnFlag++;
    return *this;
}


Logger& Logger::operator<<(long value)
{
    if (m_turnFlag != 1)
        throw std::logic_error("Wrong input order.\nError in function: Logger::operator<<");

    *m_bufiss << value;
    m_values.push_back(m_bufiss->str());
    std::ios::fmtflags fmtflags_buf = m_bufiss->flags();
    m_bufiss.reset(new std::stringstream(std::ios::in | std::ios::out));
    m_bufiss->flags(fmtflags_buf);

    m_turnFlag++;
    return *this;
}


Logger& Logger::operator<<(unsigned long value)
{
    if (m_turnFlag != 1)
        throw std::logic_error("Wrong input order.\nError in function: Logger::operator<<");

    *m_bufiss << value;
    m_values.push_back(m_bufiss->str());
    std::ios::fmtflags fmtflags_buf = m_bufiss->flags();
    m_bufiss.reset(new std::stringstream(std::ios::in | std::ios::out));
    m_bufiss->flags(fmtflags_buf);

    m_turnFlag++;
    return *this;
}


Logger& Logger::operator<<(long long value)
{
    if (m_turnFlag != 1)
        throw std::logic_error("Wrong input order.\nError in function: Logger::operator<<");

    *m_bufiss << value;
    m_values.push_back(m_bufiss->str());
    std::ios::fmtflags fmtflags_buf = m_bufiss->flags();
    m_bufiss.reset(new std::stringstream(std::ios::in | std::ios::out));
    m_bufiss->flags(fmtflags_buf);

    m_turnFlag++;
    return *this;
}


Logger& Logger::operator<<(unsigned long long value)
{
    if (m_turnFlag != 1)
        throw std::logic_error("Wrong input order.\nError in function: Logger::operator<<");

    *m_bufiss << value;
    m_values.push_back(m_bufiss->str());
    std::ios::fmtflags fmtflags_buf = m_bufiss->flags();
    m_bufiss.reset(new std::stringstream(std::ios::in | std::ios::out));
    m_bufiss->flags(fmtflags_buf);

    m_turnFlag++;
    return *this;
}


Logger& Logger::operator<<(float value)
{
    if (m_turnFlag != 1)
        throw std::logic_error("Wrong input order.\nError in function: Logger::operator<<");

    *m_bufiss << value;
    m_values.push_back(m_bufiss->str());
    std::ios::fmtflags fmtflags_buf = m_bufiss->flags();
    m_bufiss.reset(new std::stringstream(std::ios::in | std::ios::out));
    m_bufiss->flags(fmtflags_buf);

    m_turnFlag++;
    return *this;
}


Logger& Logger::operator<<(double value)
{
    if (m_turnFlag != 1)
        throw std::logic_error("Wrong input order.\nError in function: Logger::operator<<");

    *m_bufiss << value;
    m_values.push_back(m_bufiss->str());
    std::ios::fmtflags fmtflags_buf = m_bufiss->flags();
    m_bufiss.reset(new std::stringstream(std::ios::in | std::ios::out));
    m_bufiss->flags(fmtflags_buf);

    m_turnFlag++;
    return *this;
}


Logger& Logger::operator<<(long double value)
{
    if (m_turnFlag != 1)
        throw std::logic_error("Wrong input order.\nError in function: Logger::operator<<");

    *m_bufiss << value;
    m_values.push_back(m_bufiss->str());
    std::ios::fmtflags fmtflags_buf = m_bufiss->flags();
    m_bufiss.reset(new std::stringstream(std::ios::in | std::ios::out));
    m_bufiss->flags(fmtflags_buf);

    m_turnFlag++;
    return *this;
}


Logger& Logger::operator<<(bool value)
{
    if (m_turnFlag != 1)
        throw std::logic_error("Wrong input order.\nError in function: Logger::operator<<");

    *m_bufiss << value;
    m_values.push_back(m_bufiss->str());
    std::ios::fmtflags fmtflags_buf = m_bufiss->flags();
    m_bufiss.reset(new std::stringstream(std::ios::in | std::ios::out));
    m_bufiss->flags(fmtflags_buf);

    m_turnFlag++;
    return *this;
}


Logger& Logger::operator<<(const void* value)
{
    if (m_turnFlag != 1)
        throw std::logic_error("Wrong input order.\nError in function: Logger::operator<<");

    *m_bufiss << value;
    m_values.push_back(m_bufiss->str());
    std::ios::fmtflags fmtflags_buf = m_bufiss->flags();
    m_bufiss.reset(new std::stringstream(std::ios::in | std::ios::out));
    m_bufiss->flags(fmtflags_buf);

    m_turnFlag++;
    return *this;
}


Logger& Logger::operator<<(const char* value)
{
    return *this << std::string(value);
}


Logger& Logger::operator<<(const std::string& str)
{
    switch (m_turnFlag)
    {
    case 0:
        m_descriptions.push_back(str);
        m_turnFlag++;
        break;
    case 1:
        m_values.push_back(str);
        m_turnFlag++;
        break;
    case 2:
        m_endings.push_back(str);
        m_turnFlag = 0;
        break;
    }

    return *this;
}


Logger& Logger::operator<<(std::ios_base& (*func)(std::ios_base&))
{
    *m_bufiss << func;
    return *this;
}


Logger& Logger::operator<<(std::ostream& (*func)(std::ostream&))
{
    if (func != (std::ostream&(*)(std::ostream&))std::endl)
        *m_bufiss << func;
    return *this;
}

Logger& Logger::operator<<(Logger::Iomanip ioManip)
{
    switch (ioManip.manipType)
    {
    case WIDTH:     m_bufiss->width(    ioManip.param); break;
    case PRECISION: m_bufiss->precision(ioManip.param); break;
    default: throw std::range_error("Wrong tva::Logger::Iomanip value.\nError in function: tva::Logger::operator<<");
    }
    
    return *this;
}




Logger::Logger()
{
    m_bufiss.reset(new std::stringstream(std::ios::in | std::ios::out));
}


Logger::Logger(const std::string& filename, std::ios::openmode mode)
{
    m_bufiss.reset(new std::stringstream(std::ios::in | std::ios::out));
    m_file.open(filename, mode);
}


Logger::~Logger()
{
    flush();
}