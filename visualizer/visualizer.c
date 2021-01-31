/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesafi <mesafi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 10:25:27 by mesafi            #+#    #+#             */
/*   Updated: 2020/12/07 10:25:29 by mesafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <visualizer.h>

t_deque		*datum = NULL;
t_dlist		*node = NULL;
static int	carry = 0;

static void		initGL(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	gluOrtho2D(-WIDTH / 2, WIDTH / 2, -HEIGHT / 2, HEIGHT / 2);
}

void			display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawing(node);
	glFlush();
}

static void		goNext()
{
	carry = 0;
	if (!(node = node->next))
		return ;
	glutPostRedisplay();
}

static void		goPrevious()
{
	carry = 0;
	if (!(node = node->prev))
		return ;
	glutPostRedisplay();
}

static void		timer(int data)
{
	if (!carry || !(node = node->next))
		return ;
	glutPostRedisplay();
	glutTimerFunc(0, timer, 0);
}

static void		specialInput(int key, int x, int y)
{
	switch (key)
	{
		case 27:
			exit(0);
			break ;
		case 32:
			carry = !carry;
			glutTimerFunc(0, timer, 0);
			break ;
		case GLUT_KEY_UP:
		case GLUT_KEY_RIGHT:
			goNext();
			break ;
		case GLUT_KEY_DOWN:
		case GLUT_KEY_LEFT:
			goPrevious();
			break ;
		default:
			break ;
	}
}

void			visualizer(t_deque *deque)
{
	int		argc;
	char	*argv;

	argc = 0;
	datum = (t_deque *)deque;
	while (datum->front == NULL)
		;
	node = datum->front;
	glutInit(&argc, &argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("CoreWar");
	initGL();
	glutDisplayFunc(display);
	glutSpecialFunc(specialInput);
	glutMainLoop();
}