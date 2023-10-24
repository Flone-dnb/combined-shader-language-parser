#pragma once

// Standard.
#include <filesystem>
#include <string>
#include <variant>
#include <functional>

/** Parser. */
class CombinedShaderLanguageParser {
public:
    /** Groups error information. */
    struct Error {
        /**
         * Initializes error.
         *
         * @param sErrorMessage   Full error message.
         * @param pathToErrorFile Path to the file that caused the error.
         */
        Error(const std::string& sErrorMessage, const std::filesystem::path& pathToErrorFile) {
            this->sErrorMessage = sErrorMessage;
            this->pathToErrorFile = pathToErrorFile;
        }

        /** Full error message. */
        std::string sErrorMessage;

        /** Path to the file that caused the error. */
        std::filesystem::path pathToErrorFile;
    };

    /**
     * Parses the specified file as HLSL code (`#glsl` blocks are ignored and not included).
     *
     * @param pathToShaderSourceFile Path to the file to process.
     *
     * @return Error if something went wrong, otherwise full (combined) source code.
     */
    static std::variant<std::string, Error> parseHlsl(const std::filesystem::path& pathToShaderSourceFile);

    /**
     * Parses the specified file as GLSL code (`#hlsl` blocks are ignored and not included).
     *
     * @param pathToShaderSourceFile Path to the file to process.
     *
     * @return Error if something went wrong, otherwise full (combined) source code.
     */
    static std::variant<std::string, Error> parseGlsl(const std::filesystem::path& pathToShaderSourceFile);

private:
#if defined(ENABLE_ADDITIONAL_PUSH_CONSTANTS_KEYWORD)
    /**
     * Keyword used to specify variables that should be appended to the actual push constants struct
     * located in a separate file.
     */
    static inline const std::string sAdditionalPushConstantsKeyword = "#additional_push_constants";
#endif

    /**
     * Looks for the specified keyword in the specified line and calls your callback to process code
     * after keyword (i.e. body).
     *
     * @remark Will process various blocks/lines of keyword such as:
     * @code
     * #keyword CODE   // single line
     *
     * #keyword{       // curly bracket on the same line (block)
     *     CODE
     * }
     *
     * #keyword        // curly bracket on the next line (block)
     * {
     *     CODE
     * }
     * @endcode
     *
     * @param sKeyword               Keyword to look for, for example: `#hlsl`.
     * @param sLineBuffer            Current line from the file.
     * @param file                   File to read additional lines if additional push constants were found.
     * @param pathToShaderSourceFile Path to file being processed.
     * @param processContent         Callback with text (whole file line or line after keyword).
     *
     * @return Error if something went wrong.
     */
    static std::optional<Error> processKeywordCode(
        std::string_view sKeyword,
        std::string& sLineBuffer,
        std::ifstream& file,
        const std::filesystem::path& pathToShaderSourceFile,
        const std::function<void(const std::string&)>& processContent);

    /**
     * Parses the specified file.
     *
     * @param pathToShaderSourceFile Path to the file to parse.
     * @param bParseAsHlsl           Whether to parse as HLSL or as GLSL.
     *
     * @return Error if something went wrong, otherwise parsed source code.
     */
    static std::variant<std::string, Error>
    parse(const std::filesystem::path& pathToShaderSourceFile, bool bParseAsHlsl);

    /**
     * Returns input string but with GLSL types replaced to HLSL types (for example `vec3` to `float3`).
     *
     * @param sGlslCode Code with GLSL types.
     *
     * @return Input string with types replaced.
     */
    static std::string convertGlslTypesToHlslTypes(const std::string& sGlslCode);

    /**
     * Replaces all occurrences of the specified "replace from" text to "replace to" text.
     *
     * @param sText        Text to modify.
     * @param sReplaceFrom Text to replace.
     * @param sReplaceTo   Text to place instead of replaced.
     */
    static void
    replaceSubstring(std::string& sText, std::string_view sReplaceFrom, std::string_view sReplaceTo);

    /** Keyword used to specify HLSL code block/line. */
    static constexpr std::string_view sHlslKeyword = "#hlsl";

    /** Keyword used to specify GLSL code block/line. */
    static constexpr std::string_view sGlslKeyword = "#glsl";
};