void system_open(const char *path)
{
	/*char command[PATH_MAX+8];

	sprintf(command, "open \"%s\"", path);
	system(command);*/

	NSURL *fileURL = [NSURL fileURLWithPath: [NSString stringWithUTF8String: path]];

	NSWorkspace *ws = [NSWorkspace sharedWorkspace];
	[ws openURL: fileURL];
}

void system_open_url(const char *url)
{
	NSURL *fileURL = [NSURL URLWithString: [NSString stringWithUTF8String: url]];

	NSWorkspace *ws = [NSWorkspace sharedWorkspace];
	[ws openURL: fileURL];
}
