// See https://aka.ms/new-console-template for more information
using TemplateMaster;

try
{
    var templateMaster = new TemplateMasterMain();
    templateMaster.Run(args);
}
catch (Exception ex)
{
    Console.WriteLine("Template Master Error: " + ex.Message);
    return -1;
}

return 0;