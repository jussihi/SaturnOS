

void kernel_entry()
{
	char* p_video_mem = (char*) 0xb8000;

	char* hellotext = "Hello from the SaturnOS!                          ";

	char* rollText;
	while(*hellotext)
	{
		*(p_video_mem) = *(hellotext++);
		p_video_mem += 2;
	}

	while(1) {  }
	return;
}
