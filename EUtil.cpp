#include "EUtil.h"

namespace E3D {
	std::ofstream *GLogStream = nullptr;

	bool InitLog(const EString& fileName) {
		if (GLogStream == nullptr) {
			GLogStream = new std::ofstream();
			GLogStream->open(fileName.c_str());
			if (GLogStream->good()) {
				return true;
			}
			else {
				return false;
			}
		}
		return true;
	}

	void Log(const EChar *string, ...) {
		if (GLogStream == nullptr)
			return;
		EChar buffer[256];
		if (!string || !GLogStream)
			return;
		va_list arglist;
		va_start(arglist, string);
		vsprintf(buffer, string, arglist);
		va_end(arglist);

		EString info(buffer);
		*GLogStream << info << std::endl;
		GLogStream->flush();
	}
	void CloseLog() {
		GLogStream->close();
		SafeDelete(GLogStream);
	}
}