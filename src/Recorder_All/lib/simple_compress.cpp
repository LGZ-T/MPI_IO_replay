#include "simple_compress.h"

//TODO: normalize timestamp

SimpleCompress::~SimpleCompress()
{
	write_log(last_func);
}

int SimpleCompress::read_func(string line)
{
	int begin=0, end;
	string key, value;
	string test;

//	cout << "reading..." << endl;

	// unclean cur_func
	if (!cur_func.empty())
		return 1;

	for (begin=0, end=line.find(' ', begin); end>0; begin=end+1, end=line.find(' ', begin)) {
		int splitpos = line.find('=', begin);
		if (splitpos < end && splitpos != -1) {
//			cout << "A pair of key-value" << endl;
			key.assign(line, begin, splitpos-begin);	// Beware! The last para is len, not pos!!!!
			value.assign(line, splitpos+1, end-splitpos-1);
		}
		else {
			key.assign(line, begin, end-begin);
			value.assign(line, begin, end-begin);
		}
//		cout << "Key->" << key << endl << "Value->" << value << endl;
		cur_func.insert(pair<string, string>(key, value));
	}

	return 0;
}


int SimpleCompress::write_or_compress(void)	{
//	cout << "Write or compress?" << endl;
	int ret;
	if ((ret = consecutive_op(cur_func)) != 0) {
		//all_data.push_back(cur_func);
		//TODO
		write_log(last_func);
		//TODO:assign last_func as cur_func
		last_func = cur_func;
		cur_func.clear();
		
	//	cout << "Ret:" << ret << endl;
	}
	// edit last function instead of add new function in case of consecutive operation
	else {
		//K & last_func = all_data.back();

		K::iterator rep_itor = last_func.find("repetition");
		if (rep_itor == last_func.end()) {
			last_func.insert(pair<std::string, std::string>("repetition", "2"));

			K::iterator offset_itor = last_func.find("offset");
			if (offset_itor != last_func.end()) {
				last_func.insert(pair<std::string, std::string>("original_offset", last_func["offset"]));
				last_func["offset"] = cur_func["offset"];
			}
		}
		else {
			string inc = std::to_string(std::stol(rep_itor->second) + 1);
			last_func["repetition"] = inc;

			K::iterator offset_itor = last_func.find("offset");
			if (offset_itor != last_func.end()) 
				last_func["offset"] = cur_func["offset"];
		}
		cur_func.clear();	
	}

	return 0;
}

int SimpleCompress::consecutive_op(K & cur_func)
{
	if (cur_func.empty() || last_func.empty())
		return 3;

//	K last_func = all_data.back();

	if (last_func["func"] != cur_func["func"])
		return -1;
	
	K::iterator cur_itor;
	for (cur_itor=cur_func.begin(); cur_itor!=cur_func.end(); cur_itor++) {
		// check consecutive operation
		if (cur_itor->first == "offset") {
			if (std::stol(last_func["offset"]) + std::stol(last_func["count"]) != std::stol(cur_func["offset"]))
				return 1;
		}
		else if (cur_itor->first == "tm1")
			continue;
		else if (cur_itor->first == "tm2") {
			if (std::stol(cur_func["tm1"]) - std::stol(last_func["tm2"]) > 1 )	
				return 3;
			else {
				last_func["tm2"] = cur_func["tm2"];
			}
		}
		else if (cur_func[cur_itor->first] != last_func[cur_itor->first])
			return 2;
	}
	//cout << "Repetiton found!" << endl;
	return 0;
}

int SimpleCompress::write_log(K & func)
{
	//cout << "Writing.." << endl;
	K::iterator it;
	for (it=func.begin(); it!=func.end(); it++){
		os << it->first << '=' << it->second << " ";
		//cout << it->first << '=' << it->second << " ";
	}
	os << endl;

	return 0;
}

void create_sc_by_filename(SimpleCompress **sc, char *filename)
{
	cout << "create_sc_by_filename:" << filename << endl;
	*sc = new SimpleCompress(filename);
}

void delete_sc(SimpleCompress *sc)
{
	delete sc;
}

int read_func(SimpleCompress *sc, char *line)
{
	return sc->read_func(line);
}

int write_or_compress(SimpleCompress *sc)
{
	return sc->write_or_compress();
}
