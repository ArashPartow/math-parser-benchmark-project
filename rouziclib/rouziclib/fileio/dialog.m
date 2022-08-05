#include <AppKit/AppKit.h>

void mac_file_dialog_win_filter(NSSavePanel *dialog, const char *win_filter)
{
	char *f0, *f1, *p;
	int n0=1, n1;

	if (win_filter==NULL)
		return;

	f0 = calloc(strlen(win_filter)+1, sizeof(char));
	f1 = calloc(strlen(win_filter)+1, sizeof(char));

	// Parse the windows filter and put each extension into an array
	NSMutableArray *ma = [[NSMutableArray alloc] init];

	while (string_get_field(win_filter, "\1", n0, f0))	// go through \1-delimited fields
	{
		n1 = 0;
		while (string_get_field(f0, ";", n1, f1))	// go through ;-delimited subfields
		{
			p = f1;
			while (p[0]=='*' || p[0]=='.')		// skip *.
				p = &p[1];

			if (p[0])				// if there's anything left (which excludes "*.*")
				[ma addObject:[NSString stringWithUTF8String: p]];

			n1++;
		}
		n0 += 2;
	}

	// Convert mutable array to array
	NSArray *array = [NSArray arrayWithArray:ma];
	[ma release];

	// Set the array list of file types to the dialog
	if ([array count])
		[dialog setAllowedFileTypes:array];

	free(f0);
	free(f1);
}

char *open_file_dialog(const char *filter)
{
	char *path=NULL;
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	NSWindow *keyWindow = [[NSApplication sharedApplication] keyWindow];    

	NSOpenPanel *dialog = [NSOpenPanel openPanel];
	[dialog setAllowsMultipleSelection:NO];		// Disable the selection of multiple files
	[dialog setCanChooseFiles:YES];			// Enable the selection of files in the dialog
	[dialog setCanChooseDirectories:NO];		// Enable the selection of directories in the dialog

	// Add extension filters to the dialog
	mac_file_dialog_win_filter(dialog, filter);

	// Run the dialog and get the path
	if ([dialog runModal] == NSModalResponseOK)
		path = make_string_copy([[[dialog URL] path] UTF8String]);

	[pool release];
	[keyWindow makeKeyAndOrderFront:nil];

	#ifdef RL_SDL
	SDL_RaiseWindow(fb.window);
	#endif

	return path;
}

char *save_file_dialog(const char *filter)	// the filter is the UTF-8 Windows filter with \1 instead of \0
{
	char *path=NULL;
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	NSWindow *keyWindow = [[NSApplication sharedApplication] keyWindow];

	NSSavePanel *dialog = [NSSavePanel savePanel];
	[dialog setExtensionHidden:NO];

	// Add extension filters to the dialog
	mac_file_dialog_win_filter(dialog, filter);

	// Run the dialog and get the path
	if ([dialog runModal] == NSModalResponseOK)
		path = make_string_copy([[[dialog URL] path] UTF8String]);

	[pool release];
	[keyWindow makeKeyAndOrderFront:nil];

	#ifdef RL_SDL
	SDL_RaiseWindow(fb.window);
	#endif

	return path;
}
