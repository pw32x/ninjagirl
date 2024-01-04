using System;
using System.Collections.Generic;
using System.Drawing.Imaging;
using System.Drawing.Text;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;
using System.Windows.Documents;
using SceneMaster.Utils;
using SceneMaster.EditorObjectLibrary.Interfaces;
using SceneMaster.GameObjectTemplates.Models;

namespace SceneMaster.Commands.Models
{
    public class CommandLibrary : IEditorObjectInfoLibrary<CommandInfo>
    {
        private string m_commandsSourceDirectory;

        private Dictionary<string, CommandInfo> m_commandInfos = new();
        public Dictionary<string, CommandInfo> CommandInfos => m_commandInfos;

        private Dictionary<string, CommandInfo> m_failedCommandInfos = new();
        public Dictionary<string, CommandInfo> FailedCommandInfos => m_failedCommandInfos;

        internal void Load(string commandsSourceDirectory)
        {
            m_commandsSourceDirectory = commandsSourceDirectory;

            var filenames = Directory.GetFiles(m_commandsSourceDirectory, "*.*", SearchOption.AllDirectories)
                                           .Where(s => s.EndsWith(".h", StringComparison.OrdinalIgnoreCase));


            foreach (var filename in filenames)
            {
                FindCommands(filename);
            }

            // build bitmaps for each command
            BuildCommandImages();
        }

        private void FindCommands(string filename)
        {
            string contents = File.ReadAllText(filename);
            string pattern = @"\[COMMAND\s+""([^""]+)""\s+(\w+)?\]";

            // Use Regex.Match to find the first match
            Match match = Regex.Match(contents, pattern);

            string prettyFilename = "";

            int engineIndex = filename.IndexOf("engine");
            if (engineIndex != -1)
            {
                prettyFilename = filename.Substring(engineIndex);
            }

            // Loop through all matches
            while (match.Success)
            {
                // Extract description and type from the named groups
                string description = match.Groups[1].Value;
                string parameterTypeName = match.Groups[2].Value;

                var commandInfo = new CommandInfo() { Name = description,
                                                      ParameterTypeName = parameterTypeName,
                                                      Filename = prettyFilename };

                if (string.IsNullOrEmpty(description) ||
                    string.IsNullOrEmpty(parameterTypeName))
                {
                    FailedCommandInfos.Add(description,commandInfo);
                }
                else
                {
                    CommandInfos.Add(description, commandInfo);
                }

                // Move to the next match
                match = match.NextMatch();
            }
        }

        CommandInfo IEditorObjectInfoLibrary<CommandInfo>.GetEditorObjectInfo(string editorObjectInfoName)
        {
            if (!CommandInfos.TryGetValue(editorObjectInfoName, out var commandInfo))
                return null;

            return commandInfo;
        }

        private void BuildCommandImages()
        {
            string appFolder = StringUtils.EnsureTrailingSlash(AppDomain.CurrentDomain.BaseDirectory);
            string cacheDirectory = appFolder + "CommandInfoCache";

            if (!Directory.Exists(cacheDirectory))
                Directory.CreateDirectory(cacheDirectory);

            foreach (var commandInfo in CommandInfos.Values) 
            {
                string bitmapPath = StringUtils.EnsureTrailingSlash(cacheDirectory) + commandInfo.Name.Replace(" ", "_") + ".png";

                if (!File.Exists(bitmapPath))
                {
                     // Inner and outer colors
                    Color innerColor = Color.Yellow;  // Replace with your desired color
                    Color outerColor = Color.Blue;    // Replace with your desired color

                    // Create a 64x64 bitmap
                    Bitmap bitmap = new Bitmap(64, 64);

                    // Create a Graphics object from the bitmap
                    using (Graphics graphics = Graphics.FromImage(bitmap))
                    {
                        // Clear the bitmap with the outer color
                        graphics.Clear(Color.DarkBlue);

                        // Set the text format for centering
                        StringFormat stringFormat = new StringFormat();
                        stringFormat.Alignment = StringAlignment.Center;
                        stringFormat.LineAlignment = StringAlignment.Near;

                        // Create a rectangle to define the area for text
                        RectangleF rectangle = new RectangleF(0, 0, bitmap.Width, bitmap.Height);

                        // Create a brush for inner color
                        Brush innerBrush = new SolidBrush(innerColor);

                        // Use antialiasing for smoother text
                        graphics.TextRenderingHint = TextRenderingHint.SingleBitPerPixelGridFit;

                        // Split the description into words
                        string[] words = commandInfo.Name.Split(' ');

                        Font font = new Font("Arial", 8);

                        // Draw each word on a new line
                        foreach (string word in words)
                        {
                            graphics.DrawString(word, font, innerBrush, rectangle, stringFormat);
                            rectangle.Y += bitmap.Height / words.Length; // Move to the next line
                        }
                    }

                    // Save or display the resulting bitmap as needed
                    bitmap.Save(bitmapPath, ImageFormat.Png);

                    commandInfo.Visual.Image = BitmapUtils.ConvertBitmapToBitmapImage(bitmap);

                    // Dispose of resources
                    bitmap.Dispose();
                }
                else
                {
                    commandInfo.Visual.Image = BitmapUtils.LoadBitmapImage(bitmapPath);
                }
            }
        }
    }
}