#include <stdio.h>
#include "audio_bandpass.h"
#include "websocketserver.h"
#include "setqrg.h"

double audio_3k6[AUDIO_COFLEN] = {
    -0.0000606961266625744	,
-0.000258617123066649	,
0.000790865777973104	,
-0.00155272135808323	,
0.00252608646935574	,
-0.00364746050365533	,
0.00480098429396273	,
-0.00581710420144377	,
0.00647832936684909	,
-0.00653277850863011	,
0.00571520225323144	,
-0.00377404909819388	,
0.000502075919017738	,
0.00423284420237116	,
-0.0104605408627418	,
0.0180888112394362	,
-0.0268944170335244	,
0.03652706639912	,
-0.0465272066035296	,
0.0563568034034181	,
-0.0654406260653708	,
0.0732141213014954	,
-0.0791729534408305	,
0.0829188677630076	,
0.915803222655083	,
0.0829188677630076	,
-0.0791729534408305	,
0.0732141213014954	,
-0.0654406260653708	,
0.0563568034034181	,
-0.0465272066035296	,
0.03652706639912	,
-0.0268944170335244	,
0.0180888112394362	,
-0.0104605408627418	,
0.00423284420237116	,
0.000502075919017738	,
-0.00377404909819388	,
0.00571520225323144	,
-0.00653277850863011	,
0.00647832936684909	,
-0.00581710420144377	,
0.00480098429396273	,
-0.00364746050365533	,
0.00252608646935574	,
-0.00155272135808323	,
0.000790865777973104	,
-0.000258617123066649	,
-0.0000606961266625744	

};

double audio_3k0[AUDIO_COFLEN] = {
0.000864437805115849	,
-0.00122625478557066	,
0.000823163182556345	,
0.000580578556895467	,
-0.00251720606132386	,
0.00378947343949702	,
-0.00302981143606652	,
-0.000321668864459874	,
0.00518904400840732	,
-0.00887580874340664	,
0.00826838473548085	,
-0.00184350859981755	,
-0.00861557818161838	,
0.0178752127782793	,
-0.019337467741156	,
0.00877165613040208	,
0.0121056068458798	,
-0.0343990220628236	,
0.0445059684797481	,
-0.0298166770886179	,
-0.0147368119416289	,
0.0825493037595667	,
-0.156109744544835	,
0.212925993473791	,
0.765717773436333	,
0.212925993473791	,
-0.156109744544835	,
0.0825493037595667	,
-0.0147368119416289	,
-0.0298166770886179	,
0.0445059684797481	,
-0.0343990220628236	,
0.0121056068458798	,
0.00877165613040208	,
-0.019337467741156	,
0.0178752127782793	,
-0.00861557818161838	,
-0.00184350859981755	,
0.00826838473548085	,
-0.00887580874340664	,
0.00518904400840732	,
-0.000321668864459874	,
-0.00302981143606652	,
0.00378947343949702	,
-0.00251720606132386	,
0.000580578556895467	,
0.000823163182556345	,
-0.00122625478557066	,
0.000864437805115849	

};

double audio_2k4[AUDIO_COFLEN] = {
    0.000926384896021678	,
-0.000276278482690779	,
-0.00151100258507024	,
0.00179420998186381	,
0.0010650302483745	,
-0.00383256255746417	,
0.00143639469003202	,
0.00479188761370079	,
-0.00601655730027948	,
-0.00237589868715604	,
0.0107120832629853	,
-0.00494603210555155	,
-0.0115377639992562	,
0.0160455008581425	,
0.0039418536356615	,
-0.0259281804697267	,
0.0146357786141218	,
0.0260421347182318	,
-0.0424426244008038	,
-0.00523913143688591	,
0.0729105259305077	,
-0.0557852009594712	,
-0.0967281442862932	,
0.299823307136987	,
0.605744628905083	,
0.299823307136987	,
-0.0967281442862932	,
-0.0557852009594712	,
0.0729105259305077	,
-0.00523913143688591	,
-0.0424426244008038	,
0.0260421347182318	,
0.0146357786141218	,
-0.0259281804697267	,
0.0039418536356615	,
0.0160455008581425	,
-0.0115377639992562	,
-0.00494603210555155	,
0.0107120832629853	,
-0.00237589868715604	,
-0.00601655730027948	,
0.00479188761370079	,
0.00143639469003202	,
-0.00383256255746417	,
0.0010650302483745	,
0.00179420998186381	,
-0.00151100258507024	,
-0.000276278482690779	,
0.000926384896021678	

};

double audio_1k8[AUDIO_COFLEN] = {
    -0.00090200936106183	,
0.000236515663520825	,
0.00175754909449603	,
-0.0000693482602370385	,
-0.00301246642500398	,
-0.000469252820830992	,
0.00471193548043989	,
0.00161781335088183	,
-0.00685821535243301	,
-0.00368404180885706	,
0.00939905299869025	,
0.00706575387847314	,
-0.0122229858288648	,
-0.012312113738334	,
0.0151636076345592	,
0.0202970090448148	,
-0.0180133512984693	,
-0.0327326803412474	,
0.0205455378507154	,
0.0539682576090802	,
-0.0225417193857797	,
-0.100034904889746	,
0.0238200895241514	,
0.316243520611797	,
0.475739746092583	,
0.316243520611797	,
0.0238200895241514	,
-0.100034904889746	,
-0.0225417193857797	,
0.0539682576090802	,
0.0205455378507154	,
-0.0327326803412474	,
-0.0180133512984693	,
0.0202970090448148	,
0.0151636076345592	,
-0.012312113738334	,
-0.0122229858288648	,
0.00706575387847314	,
0.00939905299869025	,
-0.00368404180885706	,
-0.00685821535243301	,
0.00161781335088183	,
0.00471193548043989	,
-0.000469252820830992	,
-0.00301246642500398	,
-0.0000693482602370385	,
0.00175754909449603	,
0.000236515663520825	,
-0.00090200936106183	

};

double audio_2k8[AUDIO_COFLEN] = {
    0.00113747988914797	,
-0.00112566904904471	,
-0.000472320126058711	,
0.00264698475814706	,
-0.00292138326990423	,
-0.000211110231931613	,
0.00480839106443396	,
-0.00612703820288504	,
0.0010366907188911	,
0.00752053547628453	,
-0.0113254878836727	,
0.00411764611840682	,
0.0105413728621302	,
-0.0194122017203359	,
0.0104733727527734	,
0.0135159960960055	,
-0.032394376673095	,
0.0233861821039646	,
0.016037848019386	,
-0.0572306130368724	,
0.0551820847374606	,
0.0177299520131144	,
-0.144253220084965	,
0.26522295859818	,
0.68499267190822	,
0.26522295859818	,
-0.144253220084965	,
0.0177299520131144	,
0.0551820847374606	,
-0.0572306130368724	,
0.016037848019386	,
0.0233861821039646	,
-0.032394376673095	,
0.0135159960960055	,
0.0104733727527734	,
-0.0194122017203359	,
0.0105413728621302	,
0.00411764611840682	,
-0.0113254878836727	,
0.00752053547628453	,
0.0010366907188911	,
-0.00612703820288504	,
0.00480839106443396	,
-0.000211110231931613	,
-0.00292138326990423	,
0.00264698475814706	,
-0.000472320126058711	,
-0.00112566904904471	,
0.00113747988914797	
};

// =================================================================================
// FIR filters used by the down mixer
// =================================================================================

short audio_circular_buffer[MAX_CLIENTS][AUDIO_COFLEN];
int audio_wr_idx[MAX_CLIENTS];

short audio_filter(short sample, int client)
{
    // write value to buffer
    audio_circular_buffer[client][audio_wr_idx[client]] = sample;
    
    // increment write index
    audio_wr_idx[client]++;
    audio_wr_idx[client] %= AUDIO_COFLEN;
    
    // calculate new value
    double *pcoeff = audio_1k8;
    if(filtermode == 1) pcoeff = audio_2k4;
    if(filtermode == 2) pcoeff = audio_2k8;
    if(filtermode == 3) pcoeff = audio_3k0;
    if(filtermode == 4) pcoeff = audio_3k6;
    double y = 0;
    int idx = audio_wr_idx[client];
    for(int i = 0; i < AUDIO_COFLEN; i++)
    {
        y += (*pcoeff++ * (double)audio_circular_buffer[client][idx++]);
        if(idx >= AUDIO_COFLEN) idx=0;
    }

    if(y > 32767 || y < -32767)
        printf("audio_filter y too loud: %.0f\n",y);
    return (short)y;
}
