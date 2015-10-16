// header file

class ChromaKey : public GrassRegionFinder , public VarTypesBase
{

protected:

    VarShort* vLowThreshold_C1;
    VarShort* vLowThreshold_C2;
    VarShort* vLowThreshold_C3;

    VarShort* vHighThreshold_C1;
    VarShort* vHighThreshold_C2;
    VarShort* vHighThreshold_C3;

public:
    ChromaKey();
    ~ChromaKey();

};


// source file

ChromaKey::ChromaKey() : GrassRegionFinder()
{
//    VarListPtr mParameterList(new VarList("Chromakey Parameters"));

    vLowThreshold_C1 = new VarShort("Channel 1 - Low Threshold", 50, 0, 255);
    vLowThreshold_C2 = new VarShort("Channel 2 - Low Threshold", 50, 0, 255);
    vLowThreshold_C3 = new VarShort("Channel 3 - Low Threshold", 50, 0, 255);

    vHighThreshold_C1 = new VarShort("Channel 1 - High Threshold", 200, 0, 255);
    vHighThreshold_C2 = new VarShort("Channel 2 - High Threshold", 200, 0, 255);
    vHighThreshold_C3 = new VarShort("Channel 3 - High Threshold", 200, 0, 255);

    mParameterList->addChild(VarShortPtr(vLowThreshold_C1));
    mParameterList->addChild(VarShortPtr(vHighThreshold_C1));

    mParameterList->addChild(VarShortPtr(vLowThreshold_C2));
    mParameterList->addChild(VarShortPtr(vHighThreshold_C2));

    mParameterList->addChild(VarShortPtr(vLowThreshold_C3));
    mParameterList->addChild(VarShortPtr(vHighThreshold_C3));
}
