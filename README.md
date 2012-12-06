Games Programing 2 Coursework
=====
Tomas Zemanovic - S1033008

##Dependencies
<table border="1">
<tr>
	<th>Envirnoment variable</th>
	<th>SDK</th>
</tr>
<tr>
	<td>DXSDK_DIR</td>
	<td>DirectX 11 SDK</td>
</tr>
<tr>
	<td>HAVOKSDK_DIR</td>
	<td>Havok physics 2013.3 SIMD</td>
</tr>
<tr>
	<td>FMODSDK_DIR</td>
	<td>FMOD api</td>
</tr>
</table>
<p>Other smaller libraries were packed into 3rdParty.zip file.</p>

##Build in VS2010
1. Download 3dParty.zip from https://dl.dropbox.com/u/46186094/3rdParty.zip and save it in the root folder.
2. Unzip 3rdParty.zip, it should create 3rdParty folder in ZionNoise folder.
3. Open Source\ZNTestGame\Msvc\ZNTestGame_2010.sln
4. Build ZionNoise_2010 Project first.
5. Make sure ZNTestGame is setup as startup project.
6. Build & Run Solution.
<p>If you are using NO SIMD Havok *(getting linker error error LNK2001: unresolved external symbol "struct hkQuadReal const * const g_vectorConstants" (?g_vectorConstants@@3QBUhkQuadReal@@B)*), change ZionNoise_2012 Properties / C/C++ / Preprocessor Definitions HK_CONFIG_SIMD from 1 to 2.</p>

##Game Controls
<table border="1">
<tr>
	<td>F2</td>
	<td>Debug view / FPS view</td>
</tr>
<tr>
	<td>W</td>
	<td>Move Forward</td>
</tr>
<tr>
	<td>S</td>
	<td>Move Backard</td>
</tr>
<tr>
	<td>A</td>
	<td>Strafe Left</td>
</tr>
<tr>
	<td>D</td>
	<td>Strafe Left</td>
</tr>
<tr>
	<td>Spacebar</td>
	<td>Jump</td>
</tr>
<tr>
	<td>Ctrl + W</td>
	<td>Debug view - Move Up</td>
</tr>
<tr>
	<td>Ctrl + S</td>
	<td>Debug view - Move Down</td>
</tr>
<tr>
	<td>R</td>
	<td>Debug view - Reset Position</td>
</tr>
<tr>
	<td>Mouse move</td>
	<td>Rotate View</td>
</tr>
</table>
