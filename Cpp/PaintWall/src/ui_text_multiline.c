/*
 * ui_text_multiline.c
 *
 *  Created on: 03/02/2013
 *      Author: pedrohlc
 */

#include <paintwall.h>

#define ddp 32

_Bool UI_RenderText_Solid_MultiLine (TTF_Font *font, const char *originalText, SDL_Color fg, int bufferWidth, int bufferHeight, int x, int y) {
	if (sizeof(char) != 1) //1byte char only
		return NULL;

	SDL_Surface *buffer, *lineRGB=NULL, *lineRGBA=NULL;
	SDL_Rect input, output;
	buffer = SDL_CreateRGBSurface (SDL_SWSURFACE | SDL_SRCALPHA, bufferWidth, bufferHeight, ddp, UI_chR, UI_chG, UI_chB, UI_chA);
	int width=0, height=0, common_height=0, i;
	long length = strlen (originalText);

	char* text = (char*) malloc (length +1);
	strcpy (text, originalText);
	char* lastOccurence = text;
	length = strlen (text);

	TTF_SizeText (font, text, NULL, &common_height);

	for (i=0; i < length; i++){
		if (text[i] == '\n'){
			if (text + i == lastOccurence) {
				text[i] = 0;
				height += common_height;
				lastOccurence++;
			}else {
				text[i] = 0;

				if (lineRGBA != NULL)
					SDL_FreeSurface (lineRGBA);

				lineRGB = TTF_RenderText_Solid(font, lastOccurence, fg);
				input = (SDL_Rect) {0, 0, lineRGB->w, lineRGB->h};
				output = (SDL_Rect) {0, height, lineRGB->w, lineRGB->h};

				lineRGBA = SDL_ConvertSurface (lineRGB, &RGBAFormat, SDL_SWSURFACE | SDL_SRCALPHA);
				SDL_FreeSurface(lineRGB);

				SDL_SetAlpha(lineRGBA, 0, lineRGBA->format->alpha);
				SDL_BlitSurface (lineRGBA, &input, buffer, &output);

				if (lineRGBA->w > width)
					width = lineRGBA->w;
				height += lineRGBA->h;
				lastOccurence = (text + i + 1);
				//i++; //Jump the next
			}
		}
	}

	if (lastOccurence < (text + length) && lastOccurence[0]){
		if (lineRGBA != NULL)
			SDL_FreeSurface (lineRGBA);

		lineRGB = TTF_RenderText_Solid(font, lastOccurence, fg);
		input = (SDL_Rect) {0, 0, lineRGB->w, lineRGB->h};
		output = (SDL_Rect) {0, height, lineRGB->w, lineRGB->h};

		lineRGBA = SDL_ConvertSurface (lineRGB, &RGBAFormat, SDL_SWSURFACE | SDL_SRCALPHA);
		SDL_FreeSurface(lineRGB);

		SDL_SetAlpha(lineRGBA, 0, lineRGBA->format->alpha);
		SDL_BlitSurface (lineRGBA, &input, buffer, &output);

		if (lineRGBA->w > width)
			width = lineRGBA->w;
		height += lineRGBA->h;
	}

	if (lineRGBA != NULL)
		SDL_FreeSurface (lineRGBA);

	free (text);

	input = (SDL_Rect) {0, 0, width, height};
	output = (SDL_Rect) {x, y, width, height};
	SDL_UpdateRect (buffer, 0, 0, width, height);
	SDL_BlitSurface (buffer, &input, defaultUI.screen, &output);
	SDL_FreeSurface (buffer);

	return 1;
}

_Bool UI_RenderText_Shaded_MultiLine (TTF_Font *font, const char *originalText, SDL_Color fg, SDL_Color bg, int bufferWidth, int bufferHeight, int x, int y) {
	if (sizeof(char) != 1) //1byte char only
		return NULL;

	SDL_Surface *buffer, *lineRGB=NULL, *lineRGBA=NULL;
	SDL_Rect input, output;
	buffer = SDL_CreateRGBSurface (SDL_SWSURFACE | SDL_SRCALPHA, bufferWidth, bufferHeight, ddp, UI_chR, UI_chG, UI_chB, UI_chA);
	int width=0, height=0, common_height=0, i;
	long length = strlen (originalText);

	char* text = (char*) malloc (length +1);
	strcpy (text, originalText);
	char* lastOccurence = text;
	length = strlen (text);

	TTF_SizeText (font, text, NULL, &common_height);

	for (i=0; i < length; i++){
		if (text[i] == '\n'){
			if (text + i == lastOccurence) {
				text[i] = 0;
				height += common_height;
				lastOccurence++;
			}else {
				text[i] = 0;

				if (lineRGBA != NULL)
					SDL_FreeSurface (lineRGBA);

				lineRGB = TTF_RenderText_Shaded(font, lastOccurence, fg, bg);
				input = (SDL_Rect) {0, 0, lineRGB->w, lineRGB->h};
				output = (SDL_Rect) {0, height, lineRGB->w, lineRGB->h};

				lineRGBA = SDL_ConvertSurface (lineRGB, &RGBAFormat, SDL_SWSURFACE | SDL_SRCALPHA);
				SDL_FreeSurface(lineRGB);

				SDL_SetAlpha(lineRGBA, 0, lineRGBA->format->alpha);
				SDL_BlitSurface (lineRGBA, &input, buffer, &output);

				if (lineRGBA->w > width)
					width = lineRGBA->w;
				height += lineRGBA->h;
				lastOccurence = (text + i + 1);
				//i++; //Jump the next
			}
		}
	}

	if (lastOccurence < (text + length) && lastOccurence[0]){
		if (lineRGBA != NULL)
			SDL_FreeSurface (lineRGBA);

		lineRGB = TTF_RenderText_Shaded(font, lastOccurence, fg, bg);
		input = (SDL_Rect) {0, 0, lineRGB->w, lineRGB->h};
		output = (SDL_Rect) {0, height, lineRGB->w, lineRGB->h};

		lineRGBA = SDL_ConvertSurface (lineRGB, &RGBAFormat, SDL_SWSURFACE | SDL_SRCALPHA);
		SDL_FreeSurface(lineRGB);

		SDL_SetAlpha(lineRGBA, 0, lineRGBA->format->alpha);
		SDL_BlitSurface (lineRGBA, &input, buffer, &output);

		if (lineRGBA->w > width)
			width = lineRGBA->w;
		height += lineRGBA->h;
	}

	if (lineRGBA != NULL)
		SDL_FreeSurface (lineRGBA);

	free (text);

	input = (SDL_Rect) {0, 0, width, height};
	output = (SDL_Rect) {x, y, width, height};
	SDL_UpdateRect (buffer, 0, 0, width, height);
	SDL_BlitSurface (buffer, &input, defaultUI.screen, &output);
	SDL_FreeSurface (buffer);

	return 1;
}

_Bool UI_RenderText_Blended_MultiLine (TTF_Font *font, const char *originalText, SDL_Color fg, int bufferWidth, int bufferHeight, int x, int y) {
	if (sizeof(char) != 1) //1byte char only
		return NULL;

	SDL_Surface *buffer, *lineRGB=NULL, *lineRGBA=NULL;
	SDL_Rect input, output;
	buffer = SDL_CreateRGBSurface (SDL_SWSURFACE | SDL_SRCALPHA, bufferWidth, bufferHeight, ddp, UI_chR, UI_chG, UI_chB, UI_chA);
	int width=0, height=0, common_height=0, i;
	long length = strlen (originalText);

	char* text = (char*) malloc (length +1);
	strcpy (text, originalText);
	char* lastOccurence = text;
	length = strlen (text);

	TTF_SizeText (font, text, NULL, &common_height);

	for (i=0; i < length; i++){
		if (text[i] == '\n'){
			if (text + i == lastOccurence) {
				text[i] = 0;
				height += common_height;
				lastOccurence++;
			}else {
				text[i] = 0;

				if (lineRGBA != NULL)
					SDL_FreeSurface (lineRGBA);

				lineRGB = TTF_RenderText_Blended(font, lastOccurence, fg);
				input = (SDL_Rect) {0, 0, lineRGB->w, lineRGB->h};
				output = (SDL_Rect) {0, height, lineRGB->w, lineRGB->h};

				lineRGBA = SDL_ConvertSurface (lineRGB, &RGBAFormat, SDL_SWSURFACE | SDL_SRCALPHA);
				SDL_FreeSurface(lineRGB);

				SDL_SetAlpha(lineRGBA, 0, lineRGBA->format->alpha);
				SDL_BlitSurface (lineRGBA, &input, buffer, &output);

				if (lineRGBA->w > width)
					width = lineRGBA->w;
				height += lineRGBA->h;
				lastOccurence = (text + i + 1);
				//i++; //Jump the next
			}
		}
	}

	if (lastOccurence < (text + length) && lastOccurence[0]){
		if (lineRGBA != NULL)
			SDL_FreeSurface (lineRGBA);

		lineRGB = TTF_RenderText_Blended(font, lastOccurence, fg);
		input = (SDL_Rect) {0, 0, lineRGB->w, lineRGB->h};
		output = (SDL_Rect) {0, height, lineRGB->w, lineRGB->h};

		lineRGBA = SDL_ConvertSurface (lineRGB, &RGBAFormat, SDL_SWSURFACE | SDL_SRCALPHA);
		SDL_FreeSurface(lineRGB);

		SDL_SetAlpha(lineRGBA, 0, lineRGBA->format->alpha);
		SDL_BlitSurface (lineRGBA, &input, buffer, &output);

		if (lineRGBA->w > width)
			width = lineRGBA->w;
		height += lineRGBA->h;
	}

	if (lineRGBA != NULL)
		SDL_FreeSurface (lineRGBA);

	free (text);

	input = (SDL_Rect) {0, 0, width, height};
	output = (SDL_Rect) {x, y, width, height};
	SDL_UpdateRect (buffer, 0, 0, width, height);
	SDL_BlitSurface (buffer, &input, defaultUI.screen, &output);
	SDL_FreeSurface (buffer);

	return 1;
}
