/*This was done with <CTRL-SHIFT-L> template code.
It's conceptually easy to do a ctrl,
but tedious.  You have complete freedom.

See $LK,"CCtrl",A="MN:CCtrl"$.
*/

//Start of autocreated Code
#define SLIDER_RANGE	128
#define SLIDER_SPACING	28
#define SLIDER_BORDER	2

class CSliderState
{
	I64 left_pos;
	I64 middle_pos;
	I64 right_pos;
	CBGR24 color;
	I64 preview;
} sld;


I0 DrawPixel(I64 x, I64 y, CBGR24 color)
{
	text.fb_alias[x + y * GR_WIDTH] = color;
}

U0 DrawCtrlSlider(CDC *dc,CCtrl *c)
{
	CSliderState *s=c->state;
	
	//box
	dc->color=LTRED;
	GrRect(dc, c->left,c->top,SLIDER_SPACING*4+2,SLIDER_SPACING*2+SLIDER_RANGE);
	dc->color=BLUE;
	GrRect(dc, c->left+SLIDER_BORDER,c->top+SLIDER_BORDER,
				SLIDER_SPACING*4+2-2*SLIDER_BORDER,
				SLIDER_SPACING*2+SLIDER_RANGE-2*SLIDER_BORDER);
	//slider
	dc->color=BLACK;
	GrLine(dc,c->left+1*SLIDER_SPACING+0,c->top+SLIDER_SPACING,
				c->left+1*SLIDER_SPACING+0,c->top+SLIDER_SPACING+SLIDER_RANGE-1);
	GrLine(dc,c->left+2*SLIDER_SPACING+1,c->top+SLIDER_SPACING,
				c->left+2*SLIDER_SPACING+1,c->top+SLIDER_SPACING+SLIDER_RANGE-1);
	GrLine(dc,c->left+3*SLIDER_SPACING+2,c->top+SLIDER_SPACING,
				c->left+3*SLIDER_SPACING+2,c->top+SLIDER_SPACING+SLIDER_RANGE-1);
	//values
	dc->color=LTRED;
	GrPrint(dc,c->left+1*SLIDER_SPACING+0-FONT_WIDTH/2,
				c->top+SLIDER_SPACING+SLIDER_RANGE+3,
				"%d",s->left_pos*259/SLIDER_RANGE);
	GrPrint(dc,c->left+2*SLIDER_SPACING+0-FONT_WIDTH/2,
				c->top+SLIDER_SPACING+SLIDER_RANGE+3,
				"%d",s->middle_pos*259/SLIDER_RANGE);
	GrPrint(dc,c->left+3*SLIDER_SPACING+1-FONT_WIDTH/2,
				c->top+SLIDER_SPACING+SLIDER_RANGE+3,
				"%d",s->right_pos*259/SLIDER_RANGE);
	//knobs
	GrRect(dc,c->left+1*SLIDER_SPACING+0-3,
				c->top+SLIDER_SPACING+SLIDER_RANGE-1-s->left_pos-2,7,5);
	GrRect(dc,c->left+2*SLIDER_SPACING+1-3,
				c->top+SLIDER_SPACING+SLIDER_RANGE-1-s->middle_pos-2,7,5);
	GrRect(dc,c->left+3*SLIDER_SPACING+2-3,
				c->top+SLIDER_SPACING+SLIDER_RANGE-1-s->right_pos-2,7,5);

	dc->color=YELLOW;
	GrRect(dc,c->left+1*SLIDER_SPACING+0-2,
				c->top+SLIDER_SPACING+SLIDER_RANGE-1-s->left_pos-1,5,3);
	GrRect(dc,c->left+2*SLIDER_SPACING+1-2,
				c->top+SLIDER_SPACING+SLIDER_RANGE-1-s->middle_pos-1,5,3);
	GrRect(dc,c->left+3*SLIDER_SPACING+2-2,
				c->top+SLIDER_SPACING+SLIDER_RANGE-1-s->right_pos-1,5,3);

	//color preview
	//	I64 i, j;

	//for (i = 0; i < SLIDER_SPACING*4; i++)
	//	for (j = 0; j < 40; j++)
	//		DrawPixel(c->left +i, c->top + j, s->color);

}
public CBGR24 gr_palette_temp[16] = {
	0xFFFFFF, 0x3465A4, 0x4E9A06, 0x06989A, 0xA24444, 0x75507B, 0xCE982F, 0xBCC0B9,
	0x555753, 0x729FCF, 0x82BC49, 0x34E2E2, 0xAC3535, 0xAD7FA8, 0xFCE94F, 0x000000
};

public U0 PaletteSetTemp(Bool persistent=TRUE)
{//Activate temp palette.
	GrPaletteSet(gr_palette_temp);
	LFBFlush;
	if (persistent)
		fp_set_std_palette = &PaletteSetTemp;
}

U0 UpdateDerivedCtrlSlider(CCtrl *c)
{
	CSliderState *s=c->state;
	c->left=c->win_task->pix_width/2-(SLIDER_SPACING*3+2)/2;
	c->right=c->left+3*SLIDER_SPACING+2;
	c->top=c->win_task->pix_height/2-(SLIDER_SPACING*2+SLIDER_RANGE)/2;
	c->bottom=c->top+SLIDER_SPACING*2+SLIDER_RANGE;
	s->left_pos=ClampI64(s->left_pos,0,SLIDER_RANGE-1);
	s->middle_pos=ClampI64(s->middle_pos,0,SLIDER_RANGE-1);
	s->right_pos=ClampI64(s->right_pos,0,SLIDER_RANGE-1);
	
	I64 previewB = ClampI64(s->left_pos,0,256);
	I64 previewG = ClampI64(s->middle_pos,0,256);
	I64 previewR = ClampI64(s->right_pos,0,256);

	s->preview = previewB + previewG << 8 + previewR << 16;
	//s->color=s->preview*2;

	//gr_palette_temp = GrPaletteGet;	
	
	//gr_palette_temp[2] = preview*2;
	//PaletteSetTemp(FALSE);

}

U0 LeftClickSlider(CCtrl *c,I64 x,I64 y,Bool)
{
	CSliderState *s=c->state;
	if (x<c->left+1*SLIDER_SPACING+0+SLIDER_SPACING/3)
		s->left_pos=SLIDER_RANGE-1-(y-(c->top+SLIDER_SPACING));

	else if(x<c->left+2*SLIDER_SPACING+1+SLIDER_SPACING/3)
			s->middle_pos=SLIDER_RANGE-1-(y-(c->top+SLIDER_SPACING));
	else
		s->right_pos=SLIDER_RANGE-1-(y-(c->top+SLIDER_SPACING));

	if (c->update_derived_vals)
		(*c->update_derived_vals)(c);

	// set palette
	gr_palette_temp[15] = s->preview*2;
	PaletteSetTemp;
	LFBFlush; //why is this used?
}

CCtrl *SliderNew()
{
	CCtrl *c=CAlloc(sizeof(CCtrl));
	c->win_task=Fs;
	c->flags=CTRLF_SHOW|CTRLF_CAPTURE_LEFT_MS;
	c->type=CTRLT_GENERIC;
	c->state=&sld;
	MemSet(&sld,0,sizeof(CSliderState));
	c->draw_it=&DrawCtrlSlider;
	c->left_click=&LeftClickSlider;
	c->update_derived_vals=&UpdateDerivedCtrlSlider;
	QueueInsert(c,Fs->last_ctrl);
	TaskDerivedValsUpdate;
	return c;
}

U0 SliderDel(CCtrl *c)
{
	QueueRemove(c);
	Free(c);
}

//End of autocreated Code

U0 Main()
{
	"This is to demo ctrls.\n";
	CCtrl *c=SliderNew;
	PressAKey;
	"Left: %d Middle:%d Right: %d\n",
				sld.left_pos*10/SLIDER_RANGE,
				sld.middle_pos*10/SLIDER_RANGE,
				sld.right_pos*10/SLIDER_RANGE;
	SliderDel(c);
	DocBottom;
}

Main;
