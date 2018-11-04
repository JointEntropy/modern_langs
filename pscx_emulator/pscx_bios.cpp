#include "pscx_bios.h"

#include <fstream>
#include <iterator>

//------------------------------------------------
// TODO : to implement the loadBios function.
// It should load the BIOS binary file into array of bytes u8 (m_data).
//
// Rust:
// pub fn new(path: &Path) -> Result<Bios> {
//    let file = try!(File::open(path));
//
//    let mut data = Vec::new();
//
//    Load the BIOS
//    try!(file.take(BIOS_SIZE).read_to_end(&mut data));
//
//    if data.len() == BIOS_SIZE as usize {
//       Ok(Bios { data: data })
//    } else {
//       Err(Error::new(ErrorKind::InvalidInput,
//                      "Invalid_BIOS_size"))
//    } 
//--------------------------------------------------
Bios::BiosState Bios::loadBios(std::string path)
{

    // // TODO : to implement the loadBios function.
    // // It should load the BIOS binary file into array of bytes u8 (m_data).
    // // https://stackoverflow.com/questions/15138353/how-to-read-a-binary-file-into-a-vector-of-unsigned-chars
    // выбрасывает std::bad_cast exception
    std::basic_ifstream<char> biosFile(path, std::ios::in | std::ios::binary);

    if (!biosFile.good())
        return BIOS_STATE_INCORRECT_FILENAME;

    const uint32_t biosSize = 512 * 1024; // 512 kb

    // Load the BIOS
    m_data.insert(m_data.begin(), std::istreambuf_iterator<char>(biosFile), std::istreambuf_iterator<char>());

    biosFile.close();

    if (m_data.size() != biosSize)
        return BIOS_STATE_INVALID_BIOS_SIZE;
    //##################### old version
    // FILE *file;
    // if((file  = fopen(path.c_str(), "rb")) == NULL)
    // {
    //     return BIOS_STATE_INCORRECT_FILENAME;
    // }

    // size_t bios_size = 512 * 1024;
    // size_t bytes_readed;
    // m_data.resize(bios_size);

    // bytes_readed = fread(m_data.data(), sizeof(uint8_t), bios_size, file);

    // fclose(file);

    // if(bytes_readed != bios_size)
    //     return BIOS_STATE_INVALID_BIOS_SIZE;

    return BIOS_STATE_SUCCESS;
}

uint32_t Bios::load32(uint32_t offset) const
{
	uint32_t b0 = m_data[offset + 0];
	uint32_t b1 = m_data[offset + 1];
	uint32_t b2 = m_data[offset + 2];
	uint32_t b3 = m_data[offset + 3];

	return b0 | (b1 << 8) | (b2 << 16) | (b3 << 24);
}

uint8_t Bios::load8(uint32_t offset) const
{
	return m_data[offset];
}