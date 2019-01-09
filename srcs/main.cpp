#include "SDL.h"
#include <iostream>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>

// g++ main.cpp `pkg-config --cflags --libs sdl2`

using namespace std;

typedef struct 	s_env
{
  //THE ENVIRONMENT STRUCTURE MEANT TO EASILY STORE IMPORTANT DATA ABOUT THE STATE OF THE PROGRAM.
  //ALLOCATED ON THE STACK HERE, BUT CAN ALSO BE ALLOCATED ON THE HEAP. YOU'LL NOTICE THAT ALL THE FUNCTIONS
  //BELOW ACCEPT A POINTER. PROVIDING THEM WITH A POINTER TO SOME MALLOC-ED REGION OF MEMORY AT LEAST THE SIZE
  //OF A T_ENV SHOULD ALSO WORK.

    int         maxHeight;
	int			run;
	int			fall;
	int			ran;
	int			fell;
	int			tall;
	int			full;
	int			head;
	int			giant;
	int			warp;
	int			spread;
	int			reach;
	int			off_x;
	int			off_y;
	int			res_x;
	int			res_y;
	char		controls_display;
	char		filename_display;
	char		surprise;
    char        down;
	char		*filename;
    char        *mapstr;
	int			**map;
    Uint32      colors[5];
	SDL_Surface		*frame;
    TTF_Font    *font;
    SDL_Color   fontColor;
  int		argc;
  char		**argv;
  bool		running;
  SDL_Window	*window;
  SDL_Event	event;
}		t_env;

void *ft_memalloc(Uint32 size)
{
    void    *mem;

    mem = NULL;
    if (size > 0)
        mem = malloc(size);
    if (mem)
    {
        bzero(mem, size);
    }
    return (mem);
}

int **allocate_map(int x, int y)
{
    int **map;
    int index;

    index = 0;
    map = NULL;
    if (x > 0 && y > 0)
    {
        map = (int**)ft_memalloc(sizeof(int*) * y);
        if (map)
        {
            while (index < y)
            {
                map[index] = (int*)ft_memalloc(sizeof(int) * x);
                ++index;
            }
        }
    }
    return (map);
}

void ft_swap(int *a, int *b)
{
	int temp;

	temp = 0;
	if (a && b)
	{
		temp = *a;
		*a = *b;
		*b = temp;
	}
}

t_env	render_pt_2(t_env env)
{
	env.warp = (abs(env.run - env.ran) < \
	abs(env.fall - env.fell)) ? 1 : 0;
	if (env.warp)
	{
		ft_swap(&(env.run), &(env.fall));
		ft_swap(&(env.ran), &(env.fell));
	}
	if (env.run > env.ran)
	{
//        env.down = 1;
		ft_swap(&(env.run), &(env.ran));
		ft_swap(&(env.fall), &(env.fell));
	}
	env.spread = env.ran - env.run;
	env.reach = env.fell - env.fall;
	return (env);
}

void putdot(SDL_Surface *frame, int x, int y, Uint32 color)
{
    SDL_Rect dot;

    dot.x = x;
    dot.y = y;
    dot.h = 2;
    dot.w = 2;
    if (frame)
    {
        SDL_FillRect(frame, &dot, color);
    }
}

void	render_pt_3(t_env env)
{
	int m_new;
	int slope;
	int x;
	int y;

	m_new = abs(env.reach) * 2;
	slope = 0;
	x = env.run - 1;
	y = env.fall;
	while (++x <= env.ran)
	{
		if (env.warp)
        {
//            if (slope >= 2)
                putdot(env.frame, y + env.off_x, x + env.off_y, env.colors[3]);
//            else
//			    putdot(env.frame, y + env.off_x, x + env.off_y, env.colors[0]);
        }
		else if (env.head)
			putdot(env.frame, x + env.off_x, y + env.off_y, env.colors[1]);
		else
        {
			putdot(env.frame, x + env.off_x, y + env.off_y, env.colors[0]);
        }
		if (((slope += m_new)) > env.spread)
		{
			y += (env.reach < 0 ? -1 : 1);
			slope -= env.spread * 2;
		}
	}
}

void	render_pt_1(t_env *env, int mer, int equ)
{
	int li;

	if (env)
	{
		li = env->giant;
		env->head = env->map[mer][equ];
		env->run = ((equ * li) + (mer * li));
		env->fall = ((mer * li) / 2) - (((equ * li) + (li * env->head)) / 2);
		if (equ < env->full - 1)
		{
			env->ran = ((equ + 1) * li) + (mer * li);
			env->fell = ((mer * li) / 2) - ((((equ + 1) * li) \
			+ (li * env->map[mer][equ + 1])) / 2);
			render_pt_3(render_pt_2(*env));
		}
		if (mer < env->tall - 1)
		{
			env->ran = ((mer + 1) * li) + (equ * li);
			env->fell = (((mer + 1) * li) / 2) - (((equ * \
			li) + (li * env->map[mer + 1][equ])) / 2);
			render_pt_3(render_pt_2(*env));
		}
	}
}

int charcount(char *str, char c)
{
    int occurances;

    occurances = 0;
    while (str && c && *str)
    {
        if (*str == c)
            ++occurances;
        ++str;
    }
    return (occurances);
}

// int *atoi_array(char *str)
// {
//     int *array;
//     int bytes;
//     int numNumbers;
//     int i;
//     char *currentPosition;

//     array = NULL;
//     numNumbers = 0;
//     i = 0;
//     currentPosition = NULL;
//     if (str && strlen(str))
//     {
//         currentPosition = str;
//         numNumbers = 1 + charcount(str, ' ');
//         bytes = (numNumbers * sizeof(int));
//         array = (int*)malloc(bytes);
//         if (array)
//         {
//             bzero((void*)array, bytes);
//             while (currentPosition && *currentPosition && i < numNumbers)
//             {
//                 array[i] = atoi(currentPosition);
//                 if (*currentPosition)
//                 {
//                     currentPosition = strchr(currentPosition + 1, ' ');
//                     while (currentPosition && *currentPosition == ' ')
//                         ++currentPosition;
//                 }
//                 ++i;
//             }
//         }
//     }
//     return (array);
// }

int *atoi_array(char *str, int num_elements)
{
    int elementIndex;
    int *array;
    char *spaceLocation;


    array = NULL;
    spaceLocation = NULL;
    elementIndex = 0;
    if (num_elements && str)
    {
        array = (int*)malloc(sizeof(int)*num_elements);
        if (array)
        {
            bzero(array, (sizeof(int)*num_elements));
            while (elementIndex < num_elements)
            {
                if (str)
                    array[elementIndex] = atoi(str);
                ++elementIndex;
                spaceLocation = strchr(str, ' ');
                if (spaceLocation)
                {
                    while (*spaceLocation == ' ')
                        ++spaceLocation;
                    str = spaceLocation;
                }
            }
        }
    }
    return(array);
}

char* file_read(const char* filename) {                 // CODE FOR THIS FUNCTION SOURCED FROM SDL WIKI
        SDL_RWops *rw = SDL_RWFromFile(filename, "rb");
        if (rw == NULL) return NULL;

        Sint64 res_size = SDL_RWsize(rw);
        char* res = (char*)malloc(res_size + 1);

        Sint64 nb_read_total = 0, nb_read = 1;
        char* buf = res;
        while (nb_read_total < res_size && nb_read != 0) {
                nb_read = SDL_RWread(rw, buf, 1, (res_size - nb_read_total));
                nb_read_total += nb_read;
                buf += nb_read;
        }
        SDL_RWclose(rw);
        if (nb_read_total != res_size) {
                free(res);
                return NULL;
        }

        res[nb_read_total] = '\0';
        return res;
}

void handleKeypress(t_env *env)
{
  //EVALUATES SDL_KEYDOWN EVENTS AND RESPONDS BY EITHER CALLING AN ASSOCIATED FUNCTION OR MODIFYING A VALUE IN THE ENV.

  if (env && env->event.type == SDL_KEYDOWN)
  {
    if (env->event.key.keysym.sym == SDLK_ESCAPE)
      env->running = false;
    if (env->event.key.keysym.sym == SDLK_LEFT)
      env->off_x -= env->full * .5; //move to the left by 10*the sqrt of the width?
    if (env->event.key.keysym.sym == SDLK_RIGHT)
      env->off_x += env->full * .5; //move to the right by 10*the sqrt of the height?
    if (env->event.key.keysym.sym == SDLK_DOWN)
      env->off_y += 20; //move down by 20 units?
    if (env->event.key.keysym.sym == SDLK_UP)
      env->off_y -= 20; //move up by 20 units?
    if (env->event.key.keysym.sym == SDLK_PAGEUP && env->giant < 102)
    {
      //ZOOM IN
        env->giant += 4;
		env->off_x -= env->giant * 1.4;
		env->off_y += 8;
    }
    if (env->event.key.keysym.sym == SDLK_PAGEDOWN && env->giant > 7)
    {
      //ZOOM OUT
        env->giant -= 4;
		env->off_x += env->giant * 1.4;
		env->off_y -= 8;
    }
  }
}


int parsemap(t_env *env)
{
    int lineIndex;
    char *currentLine;
    char *cursor;
    char more = 0;


    lineIndex = 0;
    cursor = NULL;
    currentLine = NULL;
    if (env && env->mapstr)
    {
        currentLine = strtok(env->mapstr, "\n");
        if(currentLine)
        {
            env->full = atoi(currentLine);
            env->tall = atoi(strchr(currentLine, ' '));
        }
        cout<<"env->tall: "<<env->tall<<endl;
        cout<<"env->full: "<<env->full<<endl;
        if (env->tall > 0 && env->full > 0)
            env->map = allocate_map(env->full, env->tall);
        if (env->map)
        {
            while (currentLine && lineIndex < env->tall)
            {
                currentLine = strtok(NULL, "\n");
                cursor = currentLine; 
                cout<<"Current Line : "<<currentLine<<endl;
                int counter = 0;
                while (counter < env->full && currentLine && cursor)
                {
                    cout<<"element "<<counter<<" in line: " <<atoi(cursor)<<endl;
                    env->map[lineIndex][counter] = atoi(cursor);
                    cursor = strchr(cursor, ' ');
                    while(cursor && *cursor == ' ')
                        ++cursor;
                    ++counter;
                }
                lineIndex++;
            }
            // while (lineIndex < env->tall && startOfLine && strlen(startOfLine))
            // {
            //     endOfLine = strchr(startOfLine, '\n');
            //     if (endOfLine)
            //     {
            //         *endOfLine = 0;
            //         more = 1;
            //     }
            //     cout<<"Current Line : "<<startOfLine<<endl;
            //     env->map[lineIndex] = atoi_array(startOfLine);
            //     if (more && endOfLine)
            //     {
            //         startOfLine = endOfLine + 1;
            //         more = 0;
            //     }
            //     ++lineIndex;
            // }
        }
    }
}

int start(int argc, char **argv, t_env *env)
{
  //EVALUATES ARGUMENTS, CLEARS OUT ENV, LOADS HEIGHTMAP, INITIALIZES SDL & WINDOW, SETS PROGRAM IN MOTION.

  if (env && argc == 2 && strlen(argv[1]))
  {
    bzero(env, sizeof(t_env));					//CLEAN & ZERO OUT ENV'S REGION OF MEMORY TO REMOVE JUNK DATA
    env->filename = strdup(argv[1]);
    env->mapstr = file_read(env->filename);
	env->off_x = 1000 - (sqrt(pow(env->full, 2) + pow(env->tall, 2)) * 2);
	env->off_y = 500 + (env->tall / 2);
    if (env->mapstr)
    {
    parsemap(env);
    SDL_Init(SDL_INIT_EVERYTHING);				//INITIALIZE SDL
    TTF_Init();				                    //INITIALIZE SDL_TTF
    env->font = TTF_OpenFont( "LinLibertine_Rah.ttf", 28 );
    env->window = SDL_CreateWindow( "SDL_FDF",
			     SDL_WINDOWPOS_UNDEFINED,
			     SDL_WINDOWPOS_UNDEFINED,
			     2000,
			     1000,
			     0);
    env->frame = SDL_GetWindowSurface(env->window);
    env->colors[0] = SDL_MapRGB(env->frame->format, 0, 0, 255);
    env->colors[1] = SDL_MapRGB(env->frame->format, 200, 200, 255);
    env->colors[2] = SDL_MapRGB(env->frame->format, 200, 200, 100);
    env->colors[3] = SDL_MapRGB(env->frame->format, 200, 0, 100);
    env->fontColor.a = 200;
    env->fontColor.r = 255;
    env->fontColor.g = 255;
    env->fontColor.b = 255;
    env->giant = 8;
    if (env->window == NULL)					//IF THE WINDOW FAILS TO INITIALIZE...
      cout<<"Err init.window"<< endl<<SDL_GetError()<<endl;	//WE PRINT AN ERROR MESSAGE TO THE CONSOLE.
    else							//OTHERWISE...
      env->running = true;					//WE ALLOW THE MAIN EVENT LOOP TO PROCEED!
  }
}
}

void render(t_env *env)
{
    int i;
    int j;

    i = 0;
    if (env && env->frame)
    {
        SDL_Surface *message = TTF_RenderText_Solid( env->font, env->filename, env->fontColor );
        SDL_FillRect(env->frame, NULL, SDL_MapRGB(env->frame->format, 0,0,0));
        if (message)
            SDL_BlitSurface(message, NULL, env->frame, NULL);
        // putdot(env->frame, 255, 500, SDL_MapRGB(env->frame->format, 0, 0, 0));
        while (i < env->tall)
		{
			j = 0;
			while (j < env->full)
            {
				render_pt_1(env, i, j);
               //cout<<"(i, j) = "<<i<<", "<<j<<endl;
                ++j;
            }
            ++i;
		}
    }
}

void cycle(t_env *env)
{
  //HANDLES USER INPUT, RENDERS HEIGHTMAP TO WINDOW. REPEATS INDEFINITELY AFTER BEING SET IN MOTION BY "START" UNTIL AN SDL_QUIT EVENT IS DETECTED OR THE ESC KEY IS PRESSED.

  while (env->running)
  {
    while (SDL_PollEvent(&(env->event)))
    {
      if (env->event.type == SDL_QUIT)
	    env->running = false;		            //MAIN EVENT LOOP ENDS IF SDL_QUIT SIGNAL IS RECEIVED
      else
      {
        handleKeypress(env);		            //CHECK THE POLLED EVENT FOR KEYPRESSES. AND RECORD CHANGES TO THE ENV.
        render(env);                            //RENDER OR RE-RENDER THE IMAGE
        SDL_UpdateWindowSurface(env->window);   //REFRESH THE WINDOW TO SHOW THE NEW CHANGES
      }
    }
  }
}

void end (t_env *env)
{
  //CLOSE/EXIT PROCEDURE OF THE PROGRAM.

  if (env)
  {
    if (env->filename)
        free(env->filename);
    SDL_DestroyWindow(env->window);	//CLOSES THE SDL WINDOW
    SDL_Quit();				//ENDS SDL SESSION
    bzero(env, sizeof(t_env));		//WRITES OVER ENV WITH 0/NULL
  }
}

int main(int argc, char **argv)
{
  t_env env;			//ALLOCATES ENV ON STACK

  start(argc, argv, &env);	//EVALUATES PARAMETERS AND POPULATES ENV WITH NECESSARY DATA.
  cycle(&env);			//MAIN EVENT LOOP
  end(&env);			//CLEANUP AND EXIT
  return 0;
}
