#include <iostream>
#include <rocksdb/db.h>
#include <rocksdb/options.h>


int main() {
    rocksdb::DB* db;
    rocksdb::Options options;
    options.create_if_missing = true;

    rocksdb::Status status = rocksdb::DB::Open(options, "./db/data", &db);
    if (!status.ok()) {
        std::cerr << "Failed to open RocksDB: " << status.ToString() << std::endl;
        return 1;
    }

    // Write data to RocksDB
    rocksdb::WriteOptions writeOptions;
    status = db->Put(writeOptions, "key", "value");
    if (!status.ok()) {
        std::cerr << "Failed to write to RocksDB: " << status.ToString() << std::endl;
        return 1;
    }

    // Read data from RocksDB
    rocksdb::ReadOptions readOptions;
    std::string value;
    status = db->Get(readOptions, "key", &value);
    if (!status.ok()) {
        std::cerr << "Failed to read from RocksDB: " << status.ToString() << std::endl;
        return 1;
    }

    std::cout << "Value: " << value << std::endl;

    delete db;
    return 0;
}